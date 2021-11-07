
/**
 * Write a description of class PilaList here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class PilaList<T> extends VectorList implements Pila
{
    public T cima() {
        return (T) this.getPos(this.size() - 1);
    }
    
    public T desapilar() {
        return (T) this.remove();
    }
}
