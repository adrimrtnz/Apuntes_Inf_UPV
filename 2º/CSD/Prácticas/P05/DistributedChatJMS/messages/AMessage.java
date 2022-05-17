package messages;

import java.io.Serializable;


/**
 * Basic "Abstract" class for our JMS chat system.
 * 
 * <p>Just the message type is common for all messages.
 * 
 * @author Pablo Galdamez 
 */

public abstract class AMessage implements Serializable {
    
    private static final long serialVersionUID = 1L;

    public enum ChatMessageType {
        CONNECT, 
        CONNECT_OK, 
        JOIN, 
        JOIN_OK, 
        CHAT_MESSAGE, 
        USER_JOINS, 
        USER_LEAVES
    };

    private ChatMessageType type;
    
    public AMessage (ChatMessageType type) {
        this.type = type;
    } 

    /**
     * Get the message type
     * 
     * @return The message type
     */
    public ChatMessageType getType () {return type;}
}
