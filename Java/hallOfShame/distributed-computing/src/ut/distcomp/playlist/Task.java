package ut.distcomp.playlist;

import framework.NetController;

import java.util.List;
import java.util.concurrent.Callable;


class Task implements Callable<List<String>> {

    NetController netController;
    public Task(NetController netController){
        this.netController = netController;
    }
    @Override
    public List<String> call() throws Exception {
        List<String> str = null;
        while (str == null || str.isEmpty()){
            str = netController.getReceivedMsgs();
        }
        return str;
    }
}