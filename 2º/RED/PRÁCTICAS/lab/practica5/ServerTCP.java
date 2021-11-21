package practica5;

import java.util.*;
import java.net.*;
import java.io.*;

/**
 * Write a description of class ServerTCP here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ServerTCP
{
    public static void main(String args[]) 
    {
        final int PORT = 7777;
        
        try {
            ServerSocket ss = new ServerSocket(PORT);
            
            while(true) {
                Socket client = ss.accept(); // espera un cliente
                
                Scanner answer = new Scanner(client.getInputStream());
                
                PrintWriter send = new PrintWriter(client.getOutputStream(), true);
                send.printf("Se ha conectado un cliente al servidor\r\n");
                
                send.println(
                    "Datos del ServerSocket:\n\t" +
                        "Inet Address: " + ss.getInetAddress() + "\n\t" +
                        "Local Port: " + ss.getLocalPort() + "\n\n" +
                    
                    "Datos del Socket cliente:\n\t" +  
                        "Inet Adrees: " + client.getInetAddress() + "\n\t" +
                        "Local Adrees: " + client.getLocalAddress() + "\n\t" +
                        "Local Port: " + client.getLocalPort() + "\n\n"
                );
                
                //while(!answer.hasNextLine());
                String answ = answer.nextLine();
                send.printf(answ);
                
                client.close();
            }
        }
        catch (IOException e) { System.out.println(e); }
    }
}
