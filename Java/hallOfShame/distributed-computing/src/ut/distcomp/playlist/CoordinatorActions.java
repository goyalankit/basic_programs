package ut.distcomp.playlist;


import framework.Config;
import framework.NetController;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.*;

public class CoordinatorActions{
    public int procNumber;
    private NetController netController;
    private Config config;
    private ExecutorService executor = Executors.newSingleThreadExecutor();
    private String UP_SET;
    private List<String> votedYes;
    private List<String> votedNo;
    private boolean timedOut = false;
    private String DTLogFileName;

    public CoordinatorActions(NetController netController, Config config){
        this.netController = netController;
        this.config = config;
        this.UP_SET = config.lstProcess;
        votedYes = new ArrayList<String>();
        votedNo = new ArrayList<String>();
        this.DTLogFileName = "DTlog"+procNumber;
    }

    public boolean sendMessageToProcesses(String message, int[] processes){
        for(int i=0;i<processes.length;i++){
            netController.sendMsg(processes[i], message); //change this with list of processes
        }
        return true;
    }

    public void coordinate(){
    	
        String message = "I am a coordinator. Initiate three phase protocol? (yes/no).";
        String userInput = askForUserInput(message); //confirm vote-req

        if(userInput.equalsIgnoreCase("yes")){
        	//1. send vote-req to all participants along with UP_SET        	
        	//sendMessageToProcesses("vote-req,coordinator="+procNumber+""+config.listOfPorts, getAllProcessesExceptMe());
        	sendMessageToProcesses("type:vote-req;coordinator:"+procNumber+";UP_SET:"+config.lstProcess, getAllProcessesExceptMe());

        	//2. write start-PC record in DT Log
        	writeToDTlog("Started 3PC"); 
        	
        	//3. Wait for vote messages from all participants
        	List<String> response = waitForResponses(getAllProcessesExceptMe().length); //wait for response to vote-request

        	//3a. On Timeout
        	if(response.size() == 0){
        		//abort();
        		//write abort into DTLog
        		writeToDTlog("Decision:Abort");
        		return;
        	}
        	else
            	//4. Process Votes
        		processVoteResponseMessages(response);        		        	

        	//4a If at least one NO, send ABORT to all processes that voted YES and abort
        	if(votedNo.size() > 0 || timedOut == true){
        		//System.out.println("Here");
        		//write abort into DTLog
        		writeToDTlog("Decision:Abort");        		        		
        		for(int i=0;i<votedYes.size();i++){
        			System.out.println(votedYes.get(i));
        			netController.sendMsg(Integer.parseInt(votedYes.get(i)), "type:abort");
        		}
        		//System.exit(0);
        		return;
        	}
        	else{
        		//4b i) If all participants voted YES, capture coordinator input        	
        		userInput = askForUserInput("Enter coordinator's vote. yes or no");
        	
        		//If coordinator votes YES, send PRECOMMIT to all participants
        		if(userInput.equals("yes"))
        			sendMessageToProcesses("type:precommit", getAllProcessesExceptMe());
        		//If coordinator votes NO, send ABORT to all participants and abort
        		else{      
            		//write abort into DTLog
            		writeToDTlog("Decision:Abort");        			
        			sendMessageToProcesses("type:abort", getAllProcessesExceptMe());
        			System.exit(0);
        		}	
        	
        		//4b ii) If PRECOMMIT was sent, wait for ACKs from all participants
        		response.clear();
        		response = waitForResponses(getAllProcessesExceptMe().length);
        	
        		//DEBUG
        		for(int i=0;i<response.size();i++){
        			System.out.println(response.get(i));
        		}
        	
        		//4b iii) On timeout from a participant, skip that participant
        	
        		//4b iv) write commit into DTLog
        		writeToDTlog("Decision:Commit");
        		//4b v) Send commit to all participants
        		sendMessageToProcesses("type:commit", getAllProcessesExceptMe());
        		//System.exit(0);
        		
        		}
        	
        	}
        	return;

    }

    public static void abort(){
        System.exit(0);
    	//return;
    }

    public int[] getAllProcessesExceptMe(){

        int numProcesses= config.numProcesses;
        int [] processes = new int[numProcesses-1];
        int j = 0;
        for (int i=0; i<numProcesses; i++){
            if(i!=procNumber){
                processes[j] = i;
                j++;
            }
        }
        return processes;
    }
    
    public int[] getAllProcessesExceptMeThatVotedYes(){
    	//needs to be changed to get the list of processes that voted Yes
        int numProcesses= config.numProcesses;
        int [] processes = new int[numProcesses-1];
        int j = 0;
        for (int i=0; i<numProcesses; i++){
            if(i!=procNumber){
                processes[j] = i;
                j++;
            }
        }
        return processes;
    }

    public List<String> waitForResponses(int numberOfProcesses){
        System.out.println("waiting for responses");

        int numProcessesReplied = 0;
        List<String> message = new ArrayList<String>();
        Future<List<String>> [] futureTask = new Future[numberOfProcesses];
        List<String> lstTemp = null;
        timedOut = false;
        while (numProcessesReplied != numberOfProcesses){
            try {
                futureTask[numProcessesReplied] = executor.submit(new Task(netController));
                lstTemp = futureTask[numProcessesReplied].get(10, TimeUnit.SECONDS);
                for(int i=0;i<lstTemp.size();i++)
                    message.add(lstTemp.get(i));
                numProcessesReplied += lstTemp.size();
                System.out.print("*");
            } catch (TimeoutException e) {
                timedOut = true;
                return message;
            } catch (Exception e) {
                e.printStackTrace();
            }

        }
        return message;
    }

    public String askForUserInput(String message){
        Scanner reader = new Scanner(System.in);
        System.out.println(message);
        String userInput = reader.nextLine();
        return userInput;
    }
    
    public boolean processVoteResponseMessages(List<String> response){
        writeToDTlog("Processing vote responses from participants");
        //System.out.println("Response Size: " + Integer.toString(response.size()));
        for(int i=0;i<response.size();i++){
        	String [] messageInParts;
        	//System.out.println("Original Message: " + response.get(i));
        	messageInParts = response.get(i).split(":");
        	//System.out.println("Original Message Part 1: " + messageInParts[0]);
        	//System.out.println("Original Message part 2: " + messageInParts[1]);
        	if(messageInParts[1].equalsIgnoreCase("YES")){
    			votedYes.add(messageInParts[0]);
    		}
    		else
    			votedNo.add(messageInParts[0]);        	        	
        }
        //System.out.println("votedYes size: " + votedYes.size());
        //System.out.println("votedNo size: " + votedNo.size());
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
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }

    }
    
        
}
