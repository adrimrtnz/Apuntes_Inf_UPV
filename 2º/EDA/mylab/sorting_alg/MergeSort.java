package sorting_alg;

import java.util.Arrays;

/**
 * Write a description of class MergeSort here.
 * 
 * @author Adrián Martínez 
 * @version 9th Feb 2022
 */
public class MergeSort {
    public static void mergeSort(int[] in) { 
        mergeSort(in, in.length);
    }
    
    public static void mergeSort(int[] in, int n) {
        if (n < 2) { return; }
        
        int mid = n / 2;
        int[] left = new int[mid];
        int[] right = new int[n - mid];
        
        for (int i = 0; i < mid; i++) {
            left[i] = in[i];
        }
        
        for (int j = mid; j < n; j++) {
            right[j - mid] = in[j];
        }
        
        mergeSort(left, mid);
        mergeSort(right, n - mid);
        
        merge(in, left, right, mid, n - mid);
    }
    
    public static void merge(
        int[] in, int[] left, int[] right, int l_index, int r_index) {
        
         int i, j, k;
         i = j = k = 0;
         
         while (i < l_index && j < r_index) {
             if(left[i] <= right[j]) {
                 in[k++] = left[i++];
             }
             else {
                 in[k++] = right[j++];
             }
         }
         
         while (i < l_index) {
             in[k++] = left[i++];
         }
         while (j < r_index) {
             in[k++] = right[j++];
         }
     } 
     
    public static void main(String... args) {
        int[] unordered = {5,2,4,7,1,3,2,6};
        
        System.out.println("Unordered array: " + Arrays.toString(unordered));
        
        mergeSort(unordered);
        
        System.out.println("Ordered array: " + Arrays.toString(unordered));
    }
}
