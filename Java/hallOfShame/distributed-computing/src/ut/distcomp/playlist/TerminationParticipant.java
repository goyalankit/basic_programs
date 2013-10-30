package ut.distcomp.playlist;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
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

import framework.Config;
import framework.NetController;

public class TerminationParticipant {

    public int procNumber;
    private NetController netController;
    private Config config;
    private ExecutorService executor = Executors.newSingleThreadExecutor();
    //private String UP_SET; //in the format ",pi=<corresponding_port_nb>,pj=<corresponsing_port_nb>"
    private List<Integer> UP_SET;
    private static String currentCoordinator;

    private String currentState;
    private String DTLogFileName;
    TerminationCoordinatorAction terminationCoordinatorActions;
    Participant participant;
    private int viewNumber;
    private Boolean hasReceivedStateReq;
    private String sreqmsg;

    public TerminationParticipant(NetController netController, Config config, boolean isTerminationCoordinator, String currentState, List<Integer> UP_SET, Participant pt, Boolean hasReceivedStateReq, String stateReqMsg){
        this.netController = netController;
        this.config = config;
        if(isTerminationCoordinator)
        	terminationCoordinatorActions = new TerminationCoordinatorAction(netController,pt,config, UP_SET);
        this.procNumber = config.procNum;
        this.DTLogFileName = "DTlog"+procNumber+".txt";
        this.currentState = currentState;
        this.UP_SET = UP_SET;
        this.participant = pt;
        this.viewNumber = pt.getViewNumber();
        this.hasReceivedStateReq = hasReceivedStateReq;
        this.sreqmsg = stateReqMsg;
    }
    
    
    public void participate(){
    	
    	List<String> response = new ArrayList<String>();
    	System.out.println("Here0");
    	while(true){
    		while(true){
    			
    			if(!hasReceivedStateReq){
    			
    				while(true){
    				
    					//1. listens for state-req from coordinator
    					response = waitForCoordinatorMsg(netController);
    		    	
    					//2. On timeout 
    					if(response.size() == 0){
    						System.out.println("Coordinator timed out. Initiating election protocol...");
    						//Initiate Election Protocol'
    						int newCoordinator = electCoordinator();
    						//If elected
    							//Initiate Termination Coordinator's Algorithm
    						if(newCoordinator == procNumber){
    		                	TerminationParticipant coordinator = new TerminationParticipant(netController, config, true, currentState, UP_SET, participant,false, null);
    		                	coordinator.terminationCoordinatorActions.initiateNewCoordinatorProtocol();        		    						
    						}
    						return;
    					}
    					else
    					break;    		
    				}
    				System.out.println("Message received from coordinator:\n" + response.get(0));
    				//3. Process state-req message from coordinator"State: " + currentState);
        			sreqmsg = response.get(0);
    			}    	
    			
    			processStateRequestMessage(sreqmsg);

    			System.out.println("State: " + currentState);
    			//4. Send state to coordinator
    			netController.sendMsg(Integer.parseInt(currentCoordinator), "state:" + currentState);

    			//5a. Wait for response from coordinator
    			response.clear();
    			response = waitForCoordinatorMsg(netController);
        
    			//5b. On timeout
    			if(response.size() ==0){
    				//Initiate Election Protocol
    				int newCoordinator = electCoordinator();
    				//If elected
    					//Initiate Termination Coordinator's Algorithm
					if(newCoordinator == procNumber){
		                TerminationParticipant coordinator = new TerminationParticipant(netController, config, true, currentState, UP_SET, participant, false, null);
		                coordinator.terminationCoordinatorActions.initiateNewCoordinatorProtocol();        		    						
					}    				
    				return;        	
    			}
    			else
    				break;    	    	
    		}
    	
    		//5c. If coordinator sends ABORT
    		if(response.get(0).split(":")[1].equals("abort")){
    			String logEntry = readFromDTLog();
    			if(!logEntry.contains("Abort"))
    				writeToDTlog("Decision:Abort");
    		}
    		//5d. If coordinator sends COMMIT
    		else if(response.get(0).split(":")[1].equals("commit")){
    			String logEntry = readFromDTLog();
    			if(!logEntry.contains("Commit"))
    				writeToDTlog("Decision:Commit");    		
    		}
    		//5d. If coordinator sends PRE-COMMIT
    		else if(response.get(0).split(":")[1].equals("pre-commit")){
    			//send ACK to the coordinator
    			netController.sendMsg(Integer.parseInt(currentCoordinator), Integer.toString(procNumber) + ":ACK");    		

    			//5e. Wait for response from coordinator
    			response.clear();
    			response = waitForCoordinatorMsg(netController);
            
    			//5b. On timeout
    			if(response.size() ==0){
    				//Initiate Election Protocol
    				int newCoordinator = electCoordinator();
    				//If elected
    					//Initiate Termination Coordinator's Algorithm
					if(newCoordinator == procNumber){
		                TerminationParticipant coordinator = new TerminationParticipant(netController, config, true, currentState, UP_SET, participant, false, null);
		                coordinator.terminationCoordinatorActions.initiateNewCoordinatorProtocol();        		    						
					}
    				return;        	
    			}
    			else
    				break;
    		}    	
    	
    	}	
    	
    	writeToDTlog("Decision:Commit");          	
        
        return;
    }
    
    public static void abort(){
    	//write decision to DTLog
    	//writeToDTlog("Decision:Abort");
        System.exit(0);
    }


    public List<String> waitForCoordinatorMsg(NetController nc){
    	System.out.println("Here1");
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
        System.out.println("Here2");
            return message;
    }

    public String askForUserInput(String message){
        Scanner reader = new Scanner(System.in);
        System.out.println(message);
        String userInput = reader.nextLine();
        return userInput;
    }
    
    public boolean processStateRequestMessage(String message){
        writeToDTlog("Processing state request message");
        System.out.println("Processing state request message");
        String [] messageInParts;
        messageInParts = message.split(";");
        HashMap<String,String> mpParts = new HashMap<String,String>();
        writeToDTlog(message);
        String[] indParts;
        for(int i=0;i<messageInParts.length;i++){        	
        	indParts = messageInParts[i].split(":");
        	mpParts.put(indParts[0], indParts[1]);
        }        
        String str = mpParts.get("type");
        if(!str.equalsIgnoreCase("state-req")){
            writeToDTlog("Invalid Message (Non state-req) Received!");
            return false;
        }        
        currentCoordinator = mpParts.get("coordinator");
        UP_SET.remove(0);

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

    
    public String readFromDTLog(){
    	String entireFileText = ""; 
    	try {
			entireFileText = new Scanner(new File(DTLogFileName))
			    .useDelimiter("\\A").next();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
    	return entireFileText;
    }
    
    public int electCoordinator(){
    	return viewNumber % UP_SET.size();
    	
    }
    
}
