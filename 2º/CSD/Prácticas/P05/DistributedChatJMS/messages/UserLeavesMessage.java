package messages;

import static messages.AMessage.ChatMessageType.USER_LEAVES;

/**
 * Message sent from a given ChatClientJMS when it leaves the channel.
 * All clients who subscribe the channel and the server will receive it.
 * 
 * @author Pablo Galdamez
 */

public class UserLeavesMessage extends AMessage {

    private String nick;
    
    /**
     * Create a new UserLeavesMessage
     * 
     * @param nick User name who leaves
     */
    public UserLeavesMessage (String nick) {
        super (USER_LEAVES);
        this.nick = nick;
    }
    
    /**
     * Get the user name who leaves
     * 
     * @return the user name
     */
    public String getNick() {
        return nick;
    }
    
}