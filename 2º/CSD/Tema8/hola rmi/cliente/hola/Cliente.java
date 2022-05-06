 
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Cliente {

    public static void main(String[] args) {
        try {
            int port = 0;
            String host = "localhost";
            
            if (args.length == 2) {
                port = Integer.parseInt(args[1]);
            } 
            
            if (args.length >= 1) {
                host = args[0];
            }

            Registry reg = LocateRegistry.getRegistry(host, port);
            Hola h = (Hola) reg.lookup("objetoHola");      
            System.out.println(h.saluda());
            
        } catch (Exception e) {
            System.err.println("Client exception thrown: " + e.toString());
            e.printStackTrace();
        }            
    }
}
