package ejemplos.tema3;

import librerias.estructurasDeDatos.modelos.*; 
import librerias.estructurasDeDatos.deDispersion.*;
import librerias.excepciones.*;
import java.util.Date;

public class ModuloAutorizacion {
    private Map<Usuario, Date> m;
    
    public ModuloAutorizacion(int n) {
        // COMPLETAR
    }
    
    public Date fechaAcceso(String nombre, String pwd) {
        // COMPLETAR  
    }
    
    public void registrarUsuario(String nombre, String pwd) 
        throws UsuarioExistente {
        // COMPLETAR
    }
    
    public boolean estaAutorizado(String nombre, String pwd) {
        // COMPLETAR 
    }
}