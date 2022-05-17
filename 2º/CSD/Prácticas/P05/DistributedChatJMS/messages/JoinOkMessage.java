package messages;

import java.util.ArrayList;
import java.util.List;
import static messages.AMessage.ChatMessageType.JOIN_OK;

/**
 * Message sent from ChatServerJMS to a particular ChatClientJMS as join confirmation.
 * It contains the users that are currently present at the named channel.
 * 
 * @author Pablo Galdamez
 */
public class JoinOkMessage extends AMessage {
    
    private final String channelName;
    private final List<String> users;

    /**
     * Create a new JoinOK message
     * 
     * @param channelName channel name
     * @param users users list that are connected to the named channel
     */
    public JoinOkMessage(String channelName, List<String> users) {
        super (JOIN_OK);
        this.channelName = channelName;
        this.users = new ArrayList<>(users.size());
        this.users.addAll(users);
    }
    
    /**
     * Get the channel name
     * @return the channel name
     */
    public String getChannelName() {
        return channelName;
    }
    
    /**
     * Get the user list
     * @return the user list
     */
    public List<String> getUsers () {
        return users;
    }
    
}