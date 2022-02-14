package tema1;


/**
 * Write a description of class CalculateResult here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class CalculateResult extends Thread {
    private String result = "Not calculated";
    
    public void run() { result = calculate(); }
    
    private String calculate() {
        try {
            Thread.sleep(10000);
        } catch(InterruptedException e) {};
        System.out.println("Agent thread finishes its calculation");
        return "Calculation done";
    }
    
    public String getResults() { return result; }
}
