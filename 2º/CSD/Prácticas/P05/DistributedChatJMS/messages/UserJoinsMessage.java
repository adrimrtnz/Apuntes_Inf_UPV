package messages;

import static messages.AMessage.ChatMessageType.USER_JOINS;

/**
 * Message sent from ChatServerJMS to "topic" channel as broadcast to all users
 * connected to a given channel, when some user joins.
 * 
 * @author Pablo Galdamez
 */

public class UserJoinsMessage extends AMessage {

    private String nick;
    
    /**
     * Create a new UserJoins
     * 
     * @param nick User name who joins
     */
    public UserJoinsMessage (String nick) {
        super (USER_JOINS);
        this.nick = nick;
    }
    
    /**
     * Get the user name who joins
     * 
     * @return the user name
     */
    public String getNick() {
        return nick;
    }
    
}