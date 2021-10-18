package practica2;

import java.net.*;
import java.io.*;
import java.util.Scanner;


/**
 * Write a description of class ClienteDayTime here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteDayTime
{
    public static void main(String[] args) {
        
        try {
            Socket s = new Socket("zoltar.redes.upv.es", 13);
            Scanner lee = new Scanner(s.getInputStream());
            System.out.println("Conectado:\n\t" + lee.nextLine());
            s.close();
        } 
        catch(IOException e) {
           System.out.println(e.getMessage());
        }
    
    }
}
