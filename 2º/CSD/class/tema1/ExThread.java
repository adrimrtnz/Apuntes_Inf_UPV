package tema1;


/**
 * Write a description of class ExThread here.
 * 
 * @author Adrián Martínez
 * @version 9th Feb 2022
 */
public class ExThread {
    public static void main(String... args) {
        System.out.println(Thread.currentThread().getName());
        
        for (int i = 0; i < 10; i++) {
            new Thread (() -> {
                System.out.println("Executed by " + Thread.currentThread().getName());
            }, "MyThread " + i).start();
        }
    }
}