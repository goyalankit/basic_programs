package com.home.experiment;

public class SynchronizationExample {
    public static void runSynchronizationExample() throws InterruptedException{
        int count = 0;
        while(count < 10){

            ThreadExample []t = new ThreadExample[4];
            for (int i = 1; i < 5; i++) {
                t[i-1] = new ThreadExample(i);
            }

            for (int i = 1; i < 5; i++) {
                t[i-1].start();
            }

            for (int i = 1; i < 5; i++) {
                t[i-1].join();
            }

            System.err.println("Non-Synchronized value: "+ThreadExample.getCounter());
            System.out.println("Synchronized value: "+ThreadExample.getSyncCounter());

            count++;
        }
    }

}
