package practica7;

import java.net.*;

/**
 * Write a description of class dnslooup here.
 * 
 * @author Adrián Martínez 
 * @version (a version number or a date)
 */
public class dnslooup
{
    public static void main(String args[])
    {
        try 
        {
            InetAddress ip1 = InetAddress.getByName(args[0]);
            InetAddress ip2 = InetAddress.getByName(args[1]);
            
            System.out.println("Dirrección IP " + args[0] + ":\n\t" 
                + ip1.toString());
            
            System.out.println("Dirrección IP " + args[1] + ":\n\t" 
                + ip2.toString());
        } 
        catch (UnknownHostException e)
        {
            System.out.println("Host no encontrado");
        }
    }
}
