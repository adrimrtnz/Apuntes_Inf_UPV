package practica7;

import java.net.*;
import java.io.*;

/**
 * Write a description of class clienteUDP2 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class clienteUDP2
{
    public static void main(String args[])
    {
        int timeout = 3000;
        int tamBuffer = 256;
        
        try 
        {
            DatagramSocket ds = new DatagramSocket();
            //int p = ds.getLocalPort();
            //System.out.println("Puerto asociado al DatagramSocket: " + p);
            
            String name = new String("Adrian Martinez\n");
            DatagramPacket dp = new DatagramPacket(name.getBytes(),
                name.getBytes().length, InetAddress.getLocalHost(),7777);
            
            ds.send(dp);
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
