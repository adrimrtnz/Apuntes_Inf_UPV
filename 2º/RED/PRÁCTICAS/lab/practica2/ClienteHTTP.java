package practica2;

import java.net.*;
import java.io.*;
import java.util.Scanner;


/**
 * Write a description of class ClienteHTTP here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteHTTP
{
    public static void main(String[] args) {
        System.setProperty("line.separator", "\r\n");
        
        try {
            Socket s = new Socket("www.upv.es", 80);
            Scanner lee = new Scanner(s.getInputStream());     
            
            PrintWriter pw = new PrintWriter(s.getOutputStream(), true);
            pw.println("GET / HTTP/1.0\r\n\r\n");
            
            while(lee.hasNext()) {
                System.out.println(lee.nextLine());
            }
           
            s.close();
        } 
        catch(IOException e) {
           System.out.println(e.getMessage());
        }
    
    }
}
