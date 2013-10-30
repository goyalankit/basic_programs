package com.home.experiment;

import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException{

        System.out.println("type help to get list of commands");

        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        while(true){
            String[] s = in.readLine().split(" ", 2);
            String cmd = s[0];

            if(cmd.equalsIgnoreCase("srz")){
                runSerializationExample(); //(de)Serialization Example
            }else if(cmd.equalsIgnoreCase("threadex")){
                runThreadExample(); //Java Thread Examples
            }else if(cmd.equalsIgnoreCase("sncz")){
                SynchronizationExample.runSynchronizationExample(); //java synchronization example
            }else if(cmd.equalsIgnoreCase("exit")){
                System.exit(0);
            }else if(cmd.equalsIgnoreCase("help")){
                String m = "";
                m += "List of valid commands:";
                m += "\n\tsrz - run serialization example";
                m += "\n\tthreadex - run threads example";
                m += "\n\tsncz - run synchronizarion example";
                m += "\n\texit - exit the program";
                m += "\n\thelp - displays this list";
                System.err.println(m);

            }else{
                System.err.println("******** Invalid Command *******");

            }
        }

    }



    private static void runThreadExample() {
        ThreadExample t = new ThreadExample(0);
        t.start();
        System.out.println("Let me run first!");
    }


    private static void runSerializationExample() throws IOException, ClassNotFoundException{
        SubMessage m = new SubMessage(1, "hello", "world!");
        serializeMessage(m);
        m = (SubMessage)deSerializeMessage();
        System.out.println(m.getSubSomeValue());
    }


    private static void serializeMessage(Message m) throws IOException{
        FileOutputStream fileOut = new FileOutputStream("src/store/message.bak");
        ObjectOutputStream out = new ObjectOutputStream(fileOut);
        out.writeObject(m);
        out.close();
        fileOut.close();
    }

    private static Message deSerializeMessage() throws IOException, ClassNotFoundException{
        SubMessage m;
        FileInputStream fileIn = new FileInputStream("src/store/message.bak");
        ObjectInputStream oin = new ObjectInputStream(fileIn);
        m = (SubMessage) oin.readObject();
        return m;
    }

    private static void printMe(int a){
        System.out.println(a);
    }
}