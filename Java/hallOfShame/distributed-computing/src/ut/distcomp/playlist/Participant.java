package ut.distcomp.playlist;

import framework.Config;
import framework.NetController;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;


public class Participant{
    public int procNumber;
    private NetController netController;
    private Config config;
    private ExecutorService executor = Executors.newSingleThreadExecutor();
    private List<Integer> UP_SET; //in the format ",pi=<corresponding_port_nb>,pj=<corresponsing_port_nb>"
    private static String currentCoordinator;
    private int viewNumber = 0;

    private String currentState;


	private String DTLogFileName;
    CoordinatorActions coordinatorActions;


    public Participant(NetController netController, Config config, boolean isCoordinator){
        this.netController = netController;
        this.config = config;
        if(isCoordinator)
            coordinatorActions = new CoordinatorActions(netController, config);
        this.procNumber = config.procNum;
        this.DTLogFileName = "DTlog"+procNumber+".txt";
        this.UP_SET = new ArrayList<Integer>();
    }
    
    
    public void participate(){
    	//1. listens for vote-req from coordinator
    	List<String> response = waitForCoordinatorMsg(netController);

    	
    	//2. On timeout 
    	if(response.size() == 0){
    		System.out.println("Coordinator timed out. Aborting now...");
        	//abort();
        	//write abort into DTLog
    		writeToDTlog("Decision:Abort");
    		currentState = "Aborted";
    		return;
    	}
    	

    	System.out.println("Message received from coordinator:\n" + response.get(0));
    	
    	//3. Process vote-req message from coordinator
    	processVoteRequestMessage(response.get(0));
    	
    	//4. Capture participant vote
    	String userInput = askForUserInput("Enter process vote: yes or no"); 
    	System.out.println("Sending Vote");
    	
    	//4a i) If VOTE=YES, write the vote into DTLog and send the vote to the coordinator. Go to step 4a ii)
        if(userInput.equals("yes")){
        	//write vote into DTLog
        	writeToDTlog("Vote:YES");
            //netController.sendMsg(Integer.parseInt(currentCoordinator), "vote:YES;process:" + Integer.toString(procNumber));
        	netController.sendMsg(Integer.parseInt(currentCoordinator), Integer.toString(procNumber) + ":YES");
        }
        //4b. If VOTE=NO, write the vote into DTLog, send the vote to the coordinator, write the decision into DTLog and abort
        else{
        	//write vote into DTLog
        	writeToDTlog("Vote:NO");
            //netController.sendMsg(Integer.parseInt(currentCoordinator), "vote:YNO;process:" + Integer.toString(procNumber));
        	netController.sendMsg(Integer.parseInt(currentCoordinator), Integer.toString(procNumber) + ":NO");
        	//write decision into DTLog
        	writeToDTlog("Decision:Abort");
        	currentState = "Aborted";
            System.out.println("Aborting now...");
            //abort();
            return;
        }    	
        
        
        
        //4a ii) Wait for PRE-COMMIT or ABORT from coordinator
        response.clear();
        response = waitForCoordinatorMsg(netController);
        currentState = "Uncertain";
        
        //4a iii) On timeout
        if(response.size() == 0){
        	runTerminationProtocol(false, null);        	
        	return;
        }
        
        
        System.out.println("Message received from coordinator:\n" + response.get(0));
        
        //4a iv) On PRE_COMMIT from coordinator, send ACK to coordinator
        if(response.get(0).split(":")[1].equals("precommit")){
        	currentState = "Commitable";
            netController.sendMsg(Integer.parseInt(currentCoordinator), Integer.toString(procNumber) + ":ACK");
            //4a v) Wait for COMMIT from coordinator
            response.clear();
            response = waitForCoordinatorMsg(netController);
            //4a vi) On timeout
            if(response.size() ==0){
            	runTerminationProtocol(false, null);            	            	            	            	            	
            	return;
            }
            System.out.println("Message received from coordinator:\n" + response.get(0));
            if(response.get(0).split(":")[1].equals("commit")){
            	//write decision into DTLog
            	writeToDTlog("Decision:Commit");
            	currentState = "Committed";
                System.out.println("Commiting transaction...");
                //System.exit(0);
                return;
            }

        }
        else if(response.get(0).split(":")[1].equals("abort")){        	
        	System.out.println("Aborting now...");
        	//write decision into DTLog
        	writeToDTlog("Decision:Abort");
        	currentState = "Aborted";
        	return;
            //abort();
        	
        }
        //else if(){
        	
        //}
        else{
        	runTerminationProtocol(true, response.get(0));
        }
        
        return;
    }
    
    public static void abort(){
    	//write decision to DTLog
    	//writeToDTlog("Decision:Abort");
        System.exit(0);
    }


    public int getViewNumber() {
		return viewNumber;
	}


	public void setViewNumber(int viewNumber) {
		this.viewNumber = viewNumber;
	}


	public List<String> waitForCoordinatorMsg(NetController nc){
        ExecutorService executor = Executors.newSingleThreadExecutor();
        Future<List<String>> future = executor.submit(new Task(netController));
        //List<String> message = null;
        List<String> message = new ArrayList<String>();
        try {
            message = future.get(15, TimeUnit.SECONDS);

        } catch (Exception e) {
            System.out.println("time out from coordinator. initiating election protocol");// TODO initiateElectionProtocol();
            //return null;
        }
            return message;
    }

    public String askForUserInput(String message){
        Scanner reader = new Scanner(System.in);
        System.out.println(message);
        String userInput = reader.nextLine();
        return userInput;
    }
    
    public boolean processVoteRequestMessage(String message){
        writeToDTlog("Processing vote request message");
        String[] messageInParts;
        messageInParts = message.split(";");
        HashMap<String,String> mpParts = new HashMap<String,String>();
        //writeToDTlog(message);
        String[] indParts;
        for(int i=0;i<messageInParts.length;i++){        	
        	indParts = messageInParts[i].split(":");
        	mpParts.put(indParts[0], indParts[1]);
        }        
        String str = mpParts.get("type");
        if(!str.equalsIgnoreCase("vote-req")){
            writeToDTlog("Invalid Message (Non vote-req) Received!");
            return false;
        }
        //UP_SET = mpParts.get("UP_SET");
        String[] up_set_parts = mpParts.get("UP_SET").split(",");
        String[] up_set_ind;
        for(int i=1;i<up_set_parts.length;i++){
        	up_set_ind = up_set_parts[i].split("=");
        	UP_SET.add(Integer.parseInt(up_set_ind[0]));
        }
        currentCoordinator = mpParts.get("coordinator");

        return true;
    }

    public void writeToDTlog(String s) {
        FileWriter fstream = null;
        try {
            fstream = new FileWriter(DTLogFileName);
            BufferedWriter out = new BufferedWriter(fstream);
            out.write(s);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public String getCurrentState() {
		return currentState;
	}


	public void setCurrentState(String currentState) {
		this.currentState = currentState;
	}    
    
    
    public int electCoordinator(){
    	return viewNumber % UP_SET.size();
    	
    }
    
    
    public void runTerminationProtocol(Boolean hasReceivedStateReq, String msg){
    	viewNumber++;
    	//Initiate Election Protocol
    	int newCoordinator = electCoordinator();
    	/*If elected
    		//Initiate Coordinator's Termination Protocol
    	//Else
    		//Initiate Participant's Termination Protocol
    	*/
    	if(newCoordinator == procNumber){
            TerminationParticipant coordinator = new TerminationParticipant(netController, config, true, currentState, UP_SET, this, hasReceivedStateReq,msg);
            coordinator.terminationCoordinatorActions.initiateNewCoordinatorProtocol();        		
    	}
    	else{
    		//send UR-Elected to new coordinator
    		//netController.sendMsg(newCoordinator, "type:UR-Elected");
    		TerminationParticipant participant = new TerminationParticipant(netController, config, false, currentState, UP_SET, this, hasReceivedStateReq,msg);
        	participant.participate();        		
    	}        	
    	
    }
 
    
}
