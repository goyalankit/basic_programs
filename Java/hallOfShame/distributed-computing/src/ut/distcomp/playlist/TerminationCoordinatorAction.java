package ut.distcomp.playlist;


import framework.Config;
import framework.NetController;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class TerminationCoordinatorAction {

    private Config config;
    private List<Integer> UP_SET;
    private NetController netController;
    private boolean timedOut;
    private ExecutorService executor = Executors.newSingleThreadExecutor();


    private Participant participant;

    public TerminationCoordinatorAction(NetController netController, Participant pt, Config config, List<Integer> ups) {
        this.netController = netController;
        this.participant = pt;
        this.config = config;
        this.UP_SET = ups;
    }

    public void initiateNewCoordinatorProtocol() {
        //sendMessageToAllProcesses("type:state-req:"+config.procNum);
    	
    	sendMessageToAllProcesses("type:state-req;coordinator:"+config.procNum);
        List<String> messages = waitForResponses(UP_SET.size());
        processStateRequestMessages(messages);

    }

    private void processStateRequestMessages(List<String> messages) {
        config.logger.info("processing state messages....");
        String decision = null;

        List<String> states = new ArrayList<String>();


        if(participant.getCurrentState().equals("Aborted")){
        	participant.writeToDTlog("Decision:Abort");
            sendMessageToAllProcesses("type:abort");
            return;
        }else if(participant.getCurrentState().equals("Committed")){
        	participant.writeToDTlog("Decision:Coomit");
            sendMessageToAllProcesses("type:commit");
            return;
        }

        for(int i=0; i< messages.size();i++){
            String [] messageInParts = messages.get(i).split(":");
            states.add(messageInParts[1]);
        }

        //contains may not work. object comparison not by value
        if(states.contains("Aborted")){
        	participant.writeToDTlog("Deciison:Abort");
            participant.setCurrentState("Aborted");
            sendMessageToAllProcesses("type:abort");
        } else if(states.contains("Committed")){
        	participant.writeToDTlog("Decision:Commit");
            participant.setCurrentState("Committed");
            sendMessageToAllProcesses("type:commit");
        } else if(states.contains("Commitable")){ //TODO what if the process itself if committable.
        	participant.setCurrentState("Commitable");
        	participant.writeToDTlog("Decision:Pre-Commit"); //TODO do we write this??? Lecture says we don't need to.
            sendMessageToAllProcesses("type:pre-commit");
        }else{
        	participant.setCurrentState("Aborted");
        	participant.writeToDTlog("Decision:Abort");
            sendMessageToAllProcesses("type:abort");
        }
        return;
    }

    public void sendMessageToAllProcesses(String message) {
        for (int i = 0; i < UP_SET.size(); i++) {
        	if(UP_SET.get(i) != config.procNum)
        		netController.sendMsg(UP_SET.get(i), message);
        }
    }

    public List<String> waitForResponses(int numberOfProcesses){
        System.out.println("waiting for responses");

        int numProcessesReplied = 0;
        List<String> message = new ArrayList<String>();
        Future<List<String>>[] futureTask = new Future[numberOfProcesses];
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
}
