package practica2;

import java.net.*;
import java.io.*;


/**
 * Write a description of class ClienteTCP3 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteTCP3
{
    public static void main(String[] args) {
        
        try {
            Socket s = new Socket("www.upv.es", 80);
            System.out.println("Conectado:\n\t" + 
            "IP remota: " + s.getInetAddress() + "\n\t" +
            "Puerto remoto: " + s.getPort() + "\n\t"  + 
            "IP local: " + s.getLocalAddress() + "\n\t" +
            "Puerto local: " + s.getLocalPort() + "\n\t");
            s.close();
        }
        catch(NoRouteToHostException e) {
            System.out.println("No Route To Host");
        }
        catch(UnknownHostException e) {
            System.out.println("Unknown Host Exception");
        }
        catch(IOException e){
            System.out.println("IOException");
        }
}
}
