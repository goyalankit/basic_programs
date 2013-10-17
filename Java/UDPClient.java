import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class UDPClient {

    public static void main(String[] args) {
        try
        {
            DatagramSocket ds = new DatagramSocket(9999);
            byte[] buf = args[0].getBytes();

            DatagramPacket dp = new DatagramPacket(buf, buf.length, InetAddress.getByName("localhost"),5000);
            ds.send(dp);
            ds.receive(dp);
            System.out.println(new String(dp.getData()));
        }
        catch (Exception e) {
        }
    }

}
