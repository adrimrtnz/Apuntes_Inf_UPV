package practica7;

import java.net.*;
import java.io.*;
import java.util.*;

/**
 * Write a description of class daytime here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class daytime
{
    public static void main(String args[])
    {
        int timeout = 3000;
        int tamBuffer = 1024;
        int port = 7777;
        
        try 
        {
            byte[] buffer = new byte[tamBuffer];
            DatagramPacket p = new DatagramPacket(buffer, tamBuffer);
            
            Date now = new Date();
            String now_string = now.toString() + "\r\n";
            
            //DatagramPacket dp = new DatagramPacket(now_string.getBytes(),
            //    now_string.getBytes().length, InetAddress.getLocalHost(),port);
            
        
            DatagramSocket ds = new DatagramSocket(port);
            
            ds.receive(p);
            
            p.setData(now_string.getBytes());
            p.setLength(now_string.getBytes().length);
            
            ds.send(p);
            
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
