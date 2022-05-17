package utils_jms;

import java.io.IOException;
import java.io.InputStream;
import java.util.Hashtable;
import java.util.Properties;
import javax.naming.InitialContext;
import javax.naming.NamingException;

/**
 * InitialContextLoader
 * 
 * <p>When using JMS, the first step is to create an InitialContext.
 * The simplest way is to simply create a new instace. When we work this way
 * configuration is read automatically by a local file called "jndi.properties" 
 * that must exist.
 * 
 * <p>We provide this utility class to allow the instantiation of the Initial
 * Context without the need of a "jndi.properties" file. All configurable parameters
 * will be created and passed as a Hastable.
 * 
 * @author Pablo Galdamez
 */
public class InitialContextLoader {
    
    private static String theUrl = null;
    
    /**
     * Set the URL where artemis server is running
     * 
     * @param url the artemis server url
     */
    public static void setDefaultArtemisURL (String url) {
        theUrl = url;
    }
    
    /**
     * Get artemis server url
     * 
     * <p> To get the URL, this method uses the previously installed url. If 
     * absent, it tries to find the URL from a jndi.properties file.
     *     
     * @return The artemis url
     */
    public static String getArtemisURL () {
        return theUrl != null ? theUrl : loadUrlFromJndiProperties ();
    }

    
    /**
     * Get initial jndi context.
     * <p> It is created on the fly, given the artemis URL
     * 
     * @return the initial context
     * 
     * @throws NamingException Error
     */
    public static InitialContext getInitialContext () throws NamingException {
        return new InitialContext (getEnvironment (getArtemisURL()));
    }    
    
    /**
     * Create a hashtable with same configuration as it is usually found 
     * in jndi.properties.
     * 
     * @param aurl Artemis server url
     * @return Hashtable with jndi initial data
     */
    private static Hashtable<String, ?> getEnvironment (String aurl) {
        Hashtable<String, Object> jndi_env = new Hashtable<>();
        jndi_env.put(InitialContext.INITIAL_CONTEXT_FACTORY, "org.apache.activemq.artemis.jndi.ActiveMQInitialContextFactory");
        jndi_env.put("connectionFactory.ConnectionFactory", aurl);
        return jndi_env;
    }

    //    
    // TODO: We need a stable storage file to store our artemis host/port.
    // As of now, when user doens't specify the URL, we just load it from "jndi.properties", 
    // which is not such a gain.
    //
    // File could be created at the installation script, and be read here.
    //
    private static String loadUrlFromJndiProperties () {
        Properties prop = new Properties();
        InputStream input = null;
        int port = -1;
        
        try {
            
            String filename = "jndi.properties";
            input = InitialContextLoader.class.getClassLoader().getResourceAsStream(filename);
            if(input==null){
                System.out.println("No existe el fichero " + filename);
                return "";
            }
            
            prop.load(input);
            
            String cfName = prop.getProperty("connectionFactory.ConnectionFactory");
            
            String portString = (cfName.split(":"))[2];
            
            port = Integer.parseInt(portString);                        
            
        } catch (IOException ex) {
            ex.printStackTrace();
            System.exit(-1);
        } 
        
        return "tcp://localhost:" + port;
    }
            
}
