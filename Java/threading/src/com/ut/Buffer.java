package com.ut;

/**
 * Created by ankit on 8/18/14.
 */
public class Buffer {
    private int index;
    private int[] buffer = new int[10];

    public synchronized void add(int num) {
        while (index == buffer.length - 1) {
            try {
                wait();
            } catch (Exception e) {

            }
        }
        buffer[index++] = num;
        notifyAll();
        return;
    }

    public synchronized int remove() {
        while (index == 0) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        int num = buffer[--index];
        notifyAll();
        return num;
    }
}
