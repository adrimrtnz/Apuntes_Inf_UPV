package practica6;

import java.net.*;
import java.io.*;


public class ServidorConcurrente
{
  public static void main (String args[]) throws UnknownHostException, IOException
  {
      int puerto = 7777;
      
      ServerSocket servidor = new ServerSocket(puerto);
      
      while(true) {
          Socket cliente = servidor.accept();
          Servicio Cl = new Servicio(cliente);
          Cl.start();
      }
  }
}
