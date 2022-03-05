package tema5;


/**
 * Write a description of class Territorio here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Territorio
{
    private boolean[][] ocupada;
    
    public Territorio(int N) 
    {
        ocupada = new boolean[N][N];
        
        for(int i = 0; i < N; i++) 
        {
            for (int j = 0; j < N; j++)
            {
                ocupada[i][j] = false;      // la celda está libre
            }
        }
    }
    
    public synchronized void desplaza(int x0, int y0, int x, int y)
    {
        while(ocupada[x][y])
        {
            try 
            {
                wait();
            } 
            catch(InterruptedException e) {}
        }
        
        ocupada[x0][y0] = false;
        ocupada[x][y] = true;
        notifyAll();
    }
}
