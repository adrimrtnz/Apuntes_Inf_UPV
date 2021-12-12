package practica6;


/**
 * Write a description of class Ejercicio1 here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Ejercicio1 extends Thread
{
  final int N_HILOS = 3;
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
      Ejercicio1 hilo1 = new Ejercicio1("Hilo1 en ejecución.");
      Ejercicio1 hilo2 = new Ejercicio1("Hilo2 en ejecución.");
      Ejercicio1 hilo3 = new Ejercicio1("Hilo3 en ejecución.");
      
      hilo1.start();
      hilo2.start();
      hilo3.start();
  }
}
