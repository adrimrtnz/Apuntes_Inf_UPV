package messages;

import static messages.AMessage.ChatMessageType.JOIN;

/**
 * Message sent from ChatClientJMS to ChatServerJMS to join a channel
 * 
 * @author Pablo Galdamez
 */
public class JoinMessage extends AMessage {
    
    private final String channelName;
    private final String nick;
    
    /**
     * Create a new JoinMessage
     * 
     * @param channelName Channel to join
     * @param nick User name that joins
     */
    public JoinMessage (String channelName, String nick) {
        super (JOIN);
        this.nick = nick;
        this.channelName = channelName;
    }
    
    /**
     * Get the user name that joins
     * 
     * @return the user name
     */
    public String getNick() {
        return nick;
    }

    /**
     * Get the channel name where user joins
     * 
     * @return the channel name
     */
    public String getChannelName() {
        return channelName;
    }
    
}
