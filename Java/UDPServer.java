import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class UDPServer{

    public static void main(String[] args){
        try{
            DatagramSocket ds = new DatagramSocket(5000);

            byte [] buf = new byte[256];
            DatagramPacket dp = new DatagramPacket(buf, buf.length);
            try{
                ds.setSoTimeout(5000);
                ds.receive(dp);
            }
            catch(Exception r){ System.out.println("time out!");}

            System.out.println(new String(dp.getData()));

            DatagramPacket dp2 = new DatagramPacket(buf, buf.length, InetAddress.getByName("localhost"),9999);
            ds.send(dp2);

        }catch(Exception e){

        }
    }
}
