package pract5;

import java.net.*;
import java.io.*;

/**
 * Write a description of class ClienteTCP here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteTCP
{
    public static void main(String[] args) throws Exception {
        String mi_IP = args.length == 0 ? "192.168.53.131" : args[0];
        InetAddress DirIP = InetAddress.getByName(mi_IP);
        
        Socket s = new Socket("www.redes.upv.es", 80, DirIP, 40000);
        PrintWriter esc = new PrintWriter(s.getOutputStream(), true);
        esc.println("GET / HTTP/1.1");
        esc.println("Host: www.redes.upv.es");
        esc.println();
        while(true);
    }
}
