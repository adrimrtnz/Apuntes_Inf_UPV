package practica6;

import java.net.*; 
import java.io.*;
import java.util.*;

public class ejer33 extends Thread {
    Socket cliente; 

    public ejer33(Socket s) {
        cliente = s;
    }

    public void run() {
        try{
            Scanner entrada = new Scanner(cliente.getInputStream());
            String res;
                while(entrada.hasNext()){
                    res = entrada.nextLine();
                    if(res.equals("quit")) break;
                    //System.out.println(res);
                }
            cliente.close();

        }catch (UnknownHostException e){System.out.println("Error en run(): " + e);
        }catch (IOException e){System.out.println("Error en run(): " + e);}

    }

    public static void main(String args[]) throws UnknownHostException, IOException{
        ServerSocket ss=new ServerSocket(7777);

        Socket s = ss.accept();  
                    
        Scanner teclado = new Scanner(System.in);
        System.out.print("Nombre de usuario: ");
        String userName = teclado.nextLine();
        
        PrintWriter salida = new PrintWriter(s.getOutputStream(),true);
        ejer33 t = new ejer33(s);
        t.start();
        
        salida.println("---------------------------------");
        salida.println("// BIENVENIDO AL CHAT ADRIMRTNZ //");
        salida.println("---------------------------------");
        
        while(teclado.hasNextLine()){
            salida.println(userName + ": " + teclado.nextLine());
        }

        teclado.close();
        ss.close();
    }
}