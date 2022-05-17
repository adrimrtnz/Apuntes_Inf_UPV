package messages;

import static messages.AMessage.ChatMessageType.CONNECT;

/**
 * Message sent by ChatClientJMS to register into ChatServerJMS
 * 
 * @author Pablo Galdamez
 */

public class ConnectMessage extends AMessage {

    private final String nick;
    
    /**
     * Create a new ConnectMessage
     * 
     * @param nick User name that connects
     */
    public ConnectMessage (String nick) {
        super (CONNECT);
        this.nick = nick;
    }
    
    /**
     * Get the user name who connects
     * 
     * @return the user name
     */
    public String getNick() {
        return nick;
    }
    
}