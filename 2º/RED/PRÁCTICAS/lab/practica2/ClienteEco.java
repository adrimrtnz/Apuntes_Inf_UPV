package practica2;

import java.net.*;
import java.io.*;
import java.util.Scanner;


/**
 * Write a description of class ClienteEco here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteEco
{
    public static void main(String[] args) {
        
        try {
            Socket s = new Socket("zoltar.redes.upv.es", 7);
            Scanner lee = new Scanner(s.getInputStream());
            PrintWriter pw = new PrintWriter(s.getOutputStream(), true);
            
            pw.println("Hola Server!!!");
            //pw.flush();
            System.out.println(lee.nextLine());
            s.close();
        } 
        catch(IOException e) {
           System.out.println(e.getMessage());
        }
    
    }
}
