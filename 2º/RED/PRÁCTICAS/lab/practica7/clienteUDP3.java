package practica7;

import java.net.*;
import java.io.*;

/**
 * Write a description of class clienteUDP3 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class clienteUDP3
{
    public static void main(String args[])
    {
        int timeout = 3000;
        int tamBuffer = 1000;
        int port = 7777;
        
        try 
        {
            byte[] buffer = new byte[tamBuffer];
            DatagramPacket p = new DatagramPacket(buffer, tamBuffer);
            
            String name = "Adrian Martinez\n";
            DatagramPacket dp = new DatagramPacket(name.getBytes(),
                name.getBytes().length, InetAddress.getLocalHost(),port);
            
            DatagramSocket ds = new DatagramSocket();
            
            ds.setSoTimeout(timeout);
            ds.send(dp);
            ds.receive(p);
            
            String ans = new String(p.getData(), 0, p.getLength());
            System.out.println(ans);
        }
        catch (SocketException e)
        {
            System.out.println("No se ha podido crear el socket UPD");
        }
        catch (IOException e)
        {
            System.out.println(e.getMessage());
        }
    }
}
