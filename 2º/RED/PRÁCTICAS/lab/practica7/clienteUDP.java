package practica7;

import java.net.*;
import java.io.*;

/**
 * Write a description of class clienteUDP here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class clienteUDP
{
    public static void main(String args[])
    {
        try 
        {
            DatagramSocket ds = new DatagramSocket();
            int p = ds.getLocalPort();
            System.out.println("Puerto asociado al DatagramSocket: " + p);
            
            
        }
        catch (SocketException e)
        {
            System.out.println("No se ha podido crear el socket UPD");
        }
        catch (IOException e)
        {
        
        }
    }
}
