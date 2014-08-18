package com.ut;

import java.util.List;
import java.util.Random;

/**
 * Created by ankit on 8/18/14.
 */
public class Producer extends Thread {
    Buffer buffer;

    Producer(Buffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        Random r = new Random();
        while (true) {
            int num = r.nextInt(10);
            buffer.add(num);
            System.out.println("Produced num: " + num);
        }
    }

}
