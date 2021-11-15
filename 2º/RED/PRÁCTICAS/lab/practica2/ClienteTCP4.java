package practica2;

import java.net.*;
import java.io.*;
import java.util.Scanner;


/**
 * Write a description of class ClienteTCP4 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ClienteTCP4
{
    public static void main(String[] args) {
        
        final int LOWER_BOUND = 6;
        final int UPPER_BOUND = 15;
        final String MENSAJE = "Hola!";
        
        for (int i = LOWER_BOUND; i <= UPPER_BOUND; i++) {
        
            try {
                Socket s = new Socket("zoltar.redes.upv.es", i);
                Scanner entrada = new Scanner(s.getInputStream());
                PrintWriter salida = new PrintWriter(s.getOutputStream(), true);
                
                salida.println(MENSAJE);
                
                System.out.println("CONECTADO A PUERTO " + i + 
                                    ", mensaje enviado: " + MENSAJE);
                System.out.println("RESPUESTA SERVER: " + entrada.nextLine());
                
                s.close();
            }
            catch(UnknownHostException e) {
                System.out.println("Host desconocido");
                System.out.println(e);
            }
            catch(NoRouteToHostException e) {
                System.out.println("No se puede conectar");
                System.out.println(e);
            }
            catch(IOException e){
                System.out.println("Fallo en la conexión");
                System.out.println(e.getMessage());
            }
        }
    }
}
