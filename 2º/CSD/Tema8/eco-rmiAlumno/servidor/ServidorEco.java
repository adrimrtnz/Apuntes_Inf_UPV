import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

class ServidorEco  {
    static public void main (String args[]) {
       if (args.length!=1) {
            System.err.println("Uso: java ServidorEco numPuertoRegistro");
            return;
        }
       
        try {
            Registry reg=LocateRegistry.getRegistry(Integer.parseInt(args[0]));
            System.out.println("Registry en puerto "+ args[0]);
            ServicioEco srv = new ServicioEcoImpl();
            reg.rebind("Eco",srv);      // los bind y rebind solo son posibles sobre servidores
                                              // que están en la misma máquina (limitación de java.rmi)
            String[] lista;
            lista=reg.list();
            System.out.println("servicio registrado con nombre: "+lista[0]);
            System.out.println("Servidor en marcha");
        }
        catch (RemoteException e) {
            System.err.println("Error de comunicacion: " + e.toString());
            System.exit(1);
        }
        catch (Exception e) {
            System.err.println("Excepcion en ServidorEco:");
            e.printStackTrace();
            System.exit(1);
        }
    }
}
