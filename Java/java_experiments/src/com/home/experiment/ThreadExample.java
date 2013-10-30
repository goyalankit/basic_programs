package com.home.experiment;
public class ThreadExample extends Thread{

    private int action;
    private static int counter = 0;
    private static int syncCounter = 0;

    public ThreadExample(int action){
        this.action = action;
    }

    public void run(){
        callMe(action);
    }

    public static void callMe(int action){
        switch(action){
            case 0:
                System.out.println("Running inside thread!");
                break;
            case 1:
                increaseCounter100Times();
                break;
            case 2:
                decreaseCounter100Times();
                break;
            case 3:
                syncIncreaseCounter100Times();
                break;
            case 4:
                syncDecreaseCounter100Times();
                break;
            default:
                System.out.println("invalid action");
        }
    }

    private static void increaseCounter100Times() {
        int i=0;
        while(i<100){
            yield();
            counter++;
            i++;
        }
    }

    private static void decreaseCounter100Times() {
        int i=0;
        while(i<100){
            yield();
            counter--;
            i++;
        }
    }

    private static synchronized void syncIncreaseCounter100Times() {
        int i=0;
        while(i<100){
            yield();
            syncCounter++;
            i++;
        }
    }

    private static synchronized void syncDecreaseCounter100Times() {
        int i=0;
        while(i<100){
            yield();
            syncCounter--;
            i++;
        }
    }

    public static synchronized int getSyncCounter() {
        return syncCounter;
    }

    public static int getCounter() {
        return counter;
    }


}
