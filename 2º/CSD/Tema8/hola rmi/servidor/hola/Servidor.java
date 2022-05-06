// rmiregistry -J-Djava.rmi.server.useCodebaseOnly=false

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
	
public class Servidor {
  public static void main (String[] args) { 
    try {  
        Registry reg = LocateRegistry.getRegistry();      
        reg.rebind("objetoHola", new ImplHola());      
        System.out.println("Servidor Hola preparado"); 
    } catch (Exception e) {
	    System.err.println("Server exception thrown: " + e.toString());
	    e.printStackTrace();
	}
  }      
}
