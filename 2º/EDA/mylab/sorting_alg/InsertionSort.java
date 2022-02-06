package sorting_alg;


/**
 * Write a description of class InsertionSort here.
 * 
 * @author Adrián Martínez 
 * @version 6th Feb 2022
 */
public class InsertionSort
{
    static public int[] SortInt(int[] input) {
        
        for (int j = 1; j < input.length; j++) {
           int key = input[j];
           int i = j - 1;
           
           while (i >= 0 && input[i] > key) {
               input[i+1] = input[i];
               input[i--] = key;
           }
        }
        
        return input;
    }
    
    static public int[] SortIntDecreasing(int[] input) {
        
        for (int j = 1; j < input.length; j++) {
           int key = input[j];
           int i = j - 1;
           
           while (i >= 0 && input[i] < key) {
               input[i+1] = input[i];
               input[i--] = key;
           }
        }
        
        return input;
    }
}
