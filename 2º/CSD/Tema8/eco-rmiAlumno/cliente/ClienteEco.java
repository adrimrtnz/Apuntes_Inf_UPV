import java.rmi.*;
import java.rmi.registry.*;

class ClienteEco {
    static public void main (String args[]) {
        if (args.length<2) {
            System.err.println("Uso: ClienteEco hostregistro numPuertoRegistro argumentos...");
            return;
        }

       
        try {
            System.out.println("comienza el cliente");
            Registry reg=LocateRegistry.getRegistry(args[0], Integer.parseInt(args[1]));
            /* String[] lista;
            lista=reg.list();
            System.out.println(lista[0]); */
            ServicioEco srv = (ServicioEco) reg.lookup("Eco");
    
            for (int i=2; i<args.length; i++)
                System.out.println(srv.eco(args[i]));
        }
        catch (RemoteException e) {
            System.err.println("Error de comunicacion: " + e.toString());
        }
        catch (Exception e) {
            System.err.println("Excepcion en ClienteEco:");
            e.printStackTrace();
        }
    }
}
