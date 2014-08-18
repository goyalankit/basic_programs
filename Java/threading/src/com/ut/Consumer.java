package com.ut;

import java.util.Random;

/**
 * Created by ankit on 8/18/14.
 */
public class Consumer extends Thread {
    Buffer buffer;

    Consumer(Buffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        while (true) {
            int num = buffer.remove();
            System.out.println("Consumed num: " + num);
        }
    }
}
