package ut.distcomp.playlist;

import framework.Config;
import framework.NetController;

import java.io.IOException;

public class Main {

    protected static Config config;
    protected static int currentCoordinator;
    private static boolean isCoordinator=false;

    public static void main(String [] args){

        try {
            config = new Config("/home/sree/distributed-computing/input/config.properties"); //load the config file

            config.procNum = Integer.parseInt(args[0]);
            NetController netController = new NetController(config);
            
        	if(args[1].equals("true")){
        		isCoordinator = true;
        	}

            if(isCoordinator){
                Participant coordinator = new Participant(netController, config, true);
                coordinator.coordinatorActions.coordinate();

            } else{
                Participant participant = new Participant(netController, config, false);
            	participant.participate();
            }

            }
        catch (IOException e) {
            e.printStackTrace();}
        System.exit(0);
    }
}


