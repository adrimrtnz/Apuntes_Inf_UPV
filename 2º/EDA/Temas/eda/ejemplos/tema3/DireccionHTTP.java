package ejemplos.tema3;


/**
 * Write a description of class DireccionHTTP here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class DireccionHTTP
{
    private String servidor, dirRecurso;
    private int puerto;
    
    public DireccionHTTP() {}
    
    public boolean equals(Object o) {
        return o instanceof DireccionHTTP
            && this.servidor.equals(((DireccionHTTP) o).servidor)
            && this.puerto == ((DireccionHTTP) o).puerto
            && this.dirRecurso.equals(((DireccionHTTP) o).dirRecurso);
    }
    
    public int hashCode() {
        return (servidor + puerto + dirRecurso).hashCode();
    }
}
