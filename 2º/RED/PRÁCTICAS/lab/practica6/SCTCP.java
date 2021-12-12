package practica6;

import java.net.*;
import java.io.*;
import java.util.Scanner;

public class SCTCP extends Thread
{
    Socket id;
    String msg;
    
    public SCTCP (Socket s) 
    { 
        id = s; 
    }
    
    public void run()
    {
        try {
            PrintWriter salida = new PrintWriter(id.getOutputStream(), true);
            Scanner entrada = new Scanner(id.getInputStream());
            
            while(true) {
                msg = entrada.nextLine();
                if (msg.equals("quit")) { 
                    salida.println("Bye bye!");
                    break; 
                }
                salida.println(msg);
                sleep(100);
            }
        } catch (Exception e) {
            System.out.println("Error en run(): " + e); 
        }
    }
    
    public static void main (String args[]) throws IOException
    {
        ServerSocket ss = new ServerSocket(8888);
        
        while(true) {
            Socket s = ss.accept();
            SCTCP t = new SCTCP(s);
            t.start();
        }
    }
}
