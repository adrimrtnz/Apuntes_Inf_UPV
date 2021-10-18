package practica2;

import java.net.*;
import java.io.*;


/**
 * Write a description of class ClienteTCP1 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteTCP1
{
    public static void main(String[] args) throws IOException {
           Socket s = new Socket("www.upv.es", 81);
           System.out.println("Conectado:\n\t" + s);
           s.close();
        }
}
