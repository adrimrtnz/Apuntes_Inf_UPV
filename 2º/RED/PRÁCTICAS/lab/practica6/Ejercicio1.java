package practica6;


/**
 * Write a description of class Ejercicio1 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Ejercicio1 extends Thread
{
  final int REPETICIONES = 10;
  String msg;
  
  public Ejercicio1(String text) 
  {
      msg = text;
  }
  
  public void run()
  {
      try {
          for(int i = 0; i < REPETICIONES; i++)
          {
              System.out.println(msg + " Iteración: " + (i+1));
              sleep(1000);
          }
      } catch (Exception e)
      {
        System.out.println("Error en run(): " + e);
      }
  }
  
  public static void main (String args[]) 
  {
      int N_HILOS = 3;
      
      for (int i = 0; i < N_HILOS; i++) {
          String msg = "Hilo " + (i + 1) + " en ejecución,";
          Ejercicio1 h = new Ejercicio1(msg);
          h.start();
      }
  }
}
