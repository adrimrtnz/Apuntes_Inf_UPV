package practica2;

import java.net.*;
import java.io.*;
import java.util.Scanner;


/**
 * Write a description of class ClienteSMTP here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteSMTP
{
    public static void main(String[] args) {
        System.setProperty("line.separator", "\r\n");
        
        try {
            Socket s = new Socket("smtp.upv.es", 25);
            Scanner lee = new Scanner(s.getInputStream());
            System.out.println(lee.nextLine());
      
            PrintWriter pw = new PrintWriter(s.getOutputStream(), true);
            pw.println("HELO 10.236.32.170");
           
            s.close();
        } 
        catch(IOException e) {
           System.out.println(e.getMessage());
        }
    
    }
}
