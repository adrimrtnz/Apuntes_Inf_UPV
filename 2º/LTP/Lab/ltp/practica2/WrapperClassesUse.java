package practica2;

/**
 * class WrapperClassesUse.
 * 
 * @author LTP 
 * @version 2020-21
 */

public class WrapperClassesUse {        
    public static void main(String[] args) {            
        // Assignment of wrapper variables to elementary types 
        int i = new Integer(123456);		
        char c = new Character('c');
        boolean b = new Boolean(true);
            
        // Writing elementary variables
        System.out.println("int i = " + i);
        System.out.println("char c = " + c);
        System.out.println("boolean b = " + b);
               
        // Assignment of elementary values to wrapper variables
        Integer eI = 123456; 
        Character cC = 'c';
        Boolean bB = true;
            
        // Writing wrapper variables
        System.out.println("Integer I = " + eI);
        System.out.println("Character C = " + cC);
        System.out.println("Boolean B = " + bB);
    }    
}