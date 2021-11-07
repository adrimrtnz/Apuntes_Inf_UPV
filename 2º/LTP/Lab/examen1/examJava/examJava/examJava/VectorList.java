import java.util.*;

/**
 * class VectorList
 * 
 * @author LTP
 * @version 2021-22
 */ 

public class VectorList<T> implements Vector<T> {
    /** el vector se almacena como una List */
    private List<T> laLista = new ArrayList<T>();
    
    /** metodos de Coleccion<T> */
    public void add(T e) { laLista.add(e); }
    public T remove() { return laLista.remove(laLista.size() - 1);  }
    public int size() { return laLista.size(); }
    public boolean isEmpty() { return laLista.isEmpty(); }    
    public boolean isGreater(Coleccion c) { return laLista.size() > c.size(); }
    public String aCadena() { return laLista.toString(); }
    
    /** metodos de Vector<T> */
    public void addPos(int i, T e) { laLista.add(i, e); }
    public T removePos(int i) { return laLista.remove(i); }
    public T getPos(int i) { return laLista.get(i); } 
    public boolean pertenece(T e) {
        for (int i = 0; i < this.size(); i++)
        {
            T aux = remove();
            if (aux == e) { 
                add(aux);
                return true; 
            }
            else { add(aux); }
        }
        
        return false;
    }
}