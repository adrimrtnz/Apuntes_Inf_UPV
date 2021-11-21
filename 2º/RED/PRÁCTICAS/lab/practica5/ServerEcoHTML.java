package practica5;

import java.util.*;
import java.net.*;
import java.io.*;

/**
 * Write a description of class ServerEcoHTML here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ServerEcoHTML
{
    public static void main(String args[]) 
    {
        //System.setProperty("line.separator", "\r\n");
        
        final int PORT = 8000;
        
        try {
            ServerSocket ss = new ServerSocket(PORT);
            
            while(true) {
                Socket client = ss.accept(); // espera un cliente
                
                Scanner answer = new Scanner(client.getInputStream());
                PrintWriter send = new PrintWriter(client.getOutputStream(), true);
                
                send.printf("HTTP/1.0 200 OK \r\n");
                send.printf("Content-Type: text/plain \r\n");
                send.printf("\r\n");
                
                String aux = answer.nextLine();
                
                while (!aux.equals(""))
                {
                    send.println(aux + "\r\n");
                    aux = answer.nextLine();
                }
                
                client.close();
            }
        }
        catch (IOException e) { System.out.println(e); }
    }
}
