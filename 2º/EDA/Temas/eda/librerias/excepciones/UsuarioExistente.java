package librerias.excepciones;

public class UsuarioExistente extends Exception {
    public UsuarioExistente(String mensaje) {
        super(mensaje);
    }    
    public UsuarioExistente() { 
        super();
    }
}