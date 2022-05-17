//
// Students need not modify nor fully understand this file.
// The single important aspect about this Class is how to use it, not how it works.
// You can learn how to use it, reading public methods' documentation.
//

package utils_jms;

//

import utils.ProgramParameters;

// Students need not modify nor fully understand this file.
// The single important aspect about this Class is how to use it, not how it works.
//

/**
 * JMSChatConfiguration object.
 * 
 * <p>important methods are exposed as public "get_XXX" methods to get configurable parameters.
 * 
 * <p>This file provides a basic and simple command line parsing to configure our chat programs.
 * 
 * <p>A JMSChatConfiguration is always ready to be used as a singleton object. This object must be 
 * created at early stages. You can see ChatServerJMS.java or ChatClientJMS.java main() to realize 
 * where and how to create this configuration object.
 * 
 * @author Pablo Galdamez
 */

public class JMSChatConfiguration {
    
    private String url;
    
    //
    // Configuration info for the "ProgramParameters" utility where we specify parameters   
    //
    private final String [][] pp_parameters = {
        {"url", "<URL where artemis is running>"},   // No default. Default must be in "jndi.properties".
        {"nick", "<User name to use when connecting to a ChatServer>"},
        {"channel", "<Channel to auto-join when program starts>"}
    };
    
    //
    // Programs usage specification for the "ProgramParameters" utility
    //
    private final String [][] pp_programs = {
        {"ChatServerJMS", "url"},
        {"ChatRobotJMS", "url", "channel"},
        {"ChatRobot", "url", "channel"},
        {"ChatClientJMS", "url", "nick", "channel"}
    };
    
    //
    // A ProgramParameters instance tailor to our programs.
    //
    private final ProgramParameters parameters = new ProgramParameters (pp_parameters, pp_programs)
            .addChecker ("url", JMSChatConfiguration::parseUrlEx)
            .addExample ("ChatServerJMS", "url=localhost:9000", "-cp lib/*:.:")
            .addExample ("ChatServerJMS", "url=158.42.185.162:12500", "-cp lib/*:.:")
            .addExample ("ChatRobotJMS", "url=158.42.185.162:12500 channel=Linux", "-cp lib/*:.:")
            .addExample ("ChatClientJMS", "url=127.0.0.1:4000 nick=troll channel=Linux", "-cp .:lib/*")
            .addExample ("ChatClientJMS", "nick=pep", "-cp .:lib/*");

    
    //
    // Singleton pattern
    //
    private static JMSChatConfiguration the_ = null;
    
    //
    // JMSChatConfiguration makes use of "ProgramParameters" to parse command line.
    // Just matters that we can use the paramaters' "get" method.
    //
    private JMSChatConfiguration (String [] args) {
        parameters.parse (args);
        the_ = this;
    }      
    
    /**
     * Get the singleton JMSChatConfiguration object
     * 
     * @return the JMSChatConfiguration
     */
    public static JMSChatConfiguration the () {return the_;}

    
    /**
     * Create a JMSChatConfiguration from command line parameters
     * 
     * @param args vector of strings
     * 
     * @return new chatconfiguration object.
     */
    public static JMSChatConfiguration parse (String [] args) {

        // Create the chat configuration object, which in turn creates the ProgramParameters instance
        // and parses the command line searching parameters.
        //
        JMSChatConfiguration conf = new JMSChatConfiguration (args);
        
        return conf;
    }
    
    
    /**
     * Get Artemis URL
     * 
     * <p> URL is read form command line parameters. If absent, parameter is read from jndi.properties.
     * If provided url is not valir, return null, otherwise returns a normalized url on the form 
     * "tcp://address:port" where address is name or ip addresss
     * 
     * @return the url
     */
    
    public String getArtemisUrl () {
        if (url == null) url = parameters.get("url");
        if (url == null) url = InitialContextLoader.getArtemisURL();
        if (url != null ) url = normalizeUrl (url);
        if (url == null) {
            if (parameters.isProgram ("ChatServerJMS")) {
                System.out.println ("ERROR: no artemis URL as command line, nor inside a jndi.properties file.");
                parameters.usage();
            } else {
                // default for ChantClientJMS if not provided by user
                url = "tcp://localhost:10500";
            }
        }
        return url;
    }
    
    /**
     * Get user name for ChatClientJMS
     * 
     * @return the user nick, null if not provided.
     */
    public String getNick () {
        return parameters.get("nick");
    }

    /**
     * Get auto-join channel for ChatClientJMS
     * 
     * @return channel name to auto-join, null if not provided.
     */
    public String getChannelName () {
        return parameters.get("channel");
    }

    /**
     * Given an url, return its normalized version if correct. Null if wrong url.
     * 
     * @param str url on the form "host:port" or "tcp://host:port"
     * @return url on the form "tcp://host:port" or null of argument was not url.
     */    
    public static String normalizeUrl (String str) {
        try {
            String url = parseUrlEx(str);
            return url;            
        } catch (Exception e) {
            return null;
        }
    }

    private static String parseUrlEx (String str) {
        str = str.trim().toLowerCase();
        if (!str.contains(":")) throw new RuntimeException ("Wrong URL");
        String []parts = str.split(":");
        if (str.startsWith("tcp://")) {
            if (parts.length < 3) throw new RuntimeException ("Wrong URL");
            parts = new String []{parts[1], parts[2]};
            parts[0] = parts[0].substring(2);  //remove '//'                 
        }

        // hostname rules.
        int len = parts[0].length();
        if (len < 1) throw new RuntimeException ("Wrong URL");
        if (!parts[0].matches("[A-Za-z0-9.-]+")) throw new RuntimeException ("Wrong URL");
        //if (parts[0].substring(0, 1).matches("[0-9.-]")) throw  new RuntimeException ("Wrong URL");
        if (parts[0].charAt(len-1) == '-' || parts[0].charAt(len-1) == '.') throw  new RuntimeException ("Wrong URL");

        // force exception if port not a number
        int port = Integer.parseInt(parts[1]);        
        if (port < 1) throw new RuntimeException ("Wrong URL");
        
        // our urls are TCP urls
        return "tcp://" + parts[0] + ":" + parts[1];
    }
    
}
