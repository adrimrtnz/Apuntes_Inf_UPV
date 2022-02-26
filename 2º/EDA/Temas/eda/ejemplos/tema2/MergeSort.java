package ejemplos.tema2;

/**
 * class MergeSort.
 * 
 * @author FTG 
 * @version 1.0
 */

public class MergeSort {
	
    public static <T extends Comparable<T>> void mergeSort(T[] v) {
        mergeSort(v, 0, v.length - 1);
    }
        
    private static <T extends Comparable <T>> void mergeSort(
        T[] v, int i, int j) 
    {
        if (i < j) {
            int m = (i + j) / 2;       // DIVIDIR
            mergeSort(v, i, m);        // VENCER
            mergeSort(v, m + 1, j);    // VENCER
            fusionDyV(v, i, m + 1, j); // COMBINAR
        }
    }
     
    // SII los subArrays v[i, m - 1] y v[m, j] están ordenadosAsc.:
    // fusionDyV modifica el array v para que v[i,j] quede ordenadoAsc
    private static <T extends Comparable<T>> void fusionDyV(
        T[] v, int i, int m, int j) 
    {
        T[] res = (T[]) new Comparable[j - i + 1];
        int i1 = i;
        int i2 = m;
        int k = 0;
        while (i1 < m && i2 <= j) {
            if (v[i1].compareTo(v[i2]) < 0 ) res[k++] = v[i1++];
            else res[k++] = v[i2++];
        }
        for (int r = i1; r < m; r++) res[k++] = v[r];
        for (int r = i2; r <= j; r++) res[k++] = v[r];
        for (int r = 0; r < res.length; r++) v[r + i] = res[r];
    }
    
    public static <T extends Comparable<T>> T[] fusion(T[] a, T[] b) {        
        T[] res = (T[]) new Comparable[a.length + b.length];
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < a.length && j < b.length) {
            if (a[i].compareTo(b[j]) < 0) res[k++] = a[i++];
            else res[k++] = b[j++]; 
        }
        for (int r = i; r < a.length; r++) res[k++] = a[r]; 
        for (int r = j; r < b.length; r++) res[k++] = b[r]; 
        return res;
    }
}