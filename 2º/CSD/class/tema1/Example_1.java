package tema1;


/**
 * Write a description of class Example_1 here.
 * 
 * @author Adrián Martínez
 * @version 9th Feb 2022
 */
public class Example_1
{
    public static void main(String... args) {
        CalculateResult agent = new CalculateResult();
        agent.start();
        
        System.out.println("Main in execution");
        
        // Espera activa
        while(agent.isAlive()) {
            Thread.yield();
        }
        
        /*
         * try {
         *     agent.join();
         *     ...
         *  }
         */
        
        System.out.println(agent.getResults());
    }
}
