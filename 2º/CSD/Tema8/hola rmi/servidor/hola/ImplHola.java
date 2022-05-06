import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

class ImplHola extends UnicastRemoteObject implements Hola {
  ImplHola() throws RemoteException {
    super();
  }
  
  public String saluda() throws RemoteException {
    System.out.println("Método remoto saluda() llamado"); 
    return "Hola a todos";
  }      
}
