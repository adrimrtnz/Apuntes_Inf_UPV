package ejemplos.tema2;


/**
 * Write a description of class RecursionNumerica here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class RecursionNumerica
{
    /**
     *  n >= 0
     */
    static int fibonacci(int n)
    {
        if (n <= 1 && !(n < 0)) { return n; }        
        return fibonacci(n-1) + fibonacci(n-2);
    }
    
    static int factorial(int n)
    {
        if (n <= 1) { return 1; }
        
        else 
        {
            return n * factorial(n-1);
        }
    }
    
    static int maximoComunDivisor(int n, int m) 
    {
        if (n == m) { return n; }
        else if (n > m) { return maximoComunDivisor(n-m, m); }
        else { return maximoComunDivisor(n, m-n); }
    }
    
    static int sumar(Integer[] v)
    {
        return sumar(v, 0);
    }
    
    private static int sumar(Integer[] v, int inicio)
    {
        if (inicio == v.length) { return 0; }
        
        return v[inicio] + sumar(v, inicio + 1);
    }
    
    /**
     * a >= 0 AND b >= 0
     */
    static int multiplicar(int a, int b)
    {
        if (a == 0) return 0;
        return multiplicar(a - 1,b) + b;
    }
    
    static int multiplicarMinimo(int a, int b)
    {
        if (a < b) return multiplicar(a, b);
        return multiplicar(b, a);
    }
    
    static int multiplicarRL(int a, int b)
    {
        if (a == 0) return 0;
        if (a % 2 == 0) 
        {
            return multiplicarRL(a/2, b) * 2;
        } else 
        {
            return multiplicarRL(a/2, b) * 2 + b;
        }
    }
}
