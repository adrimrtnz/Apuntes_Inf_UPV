package messages;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import static messages.AMessage.ChatMessageType.CONNECT_OK;

/**
 * Message sent from ChatServerJMS to ChatClientJMS as confirmation of connection
 * 
 * @author Pablo Galdamez
 *
 */
public class ConnectOkMessage extends AMessage {

    private final List<String> users = new ArrayList<>();
    private final List<String> channels = new ArrayList<>();
    
    /**
     * Create the message with initial user and channel list
     * 
     * @param users Server user list
     * @param channels channel list
     */
    public ConnectOkMessage(Collection<String> users, Collection<String> channels) {
        super (CONNECT_OK);
        if (users != null) this.users.addAll(users);
        if (channels != null) this.channels.addAll(channels);
    }
    
    /**
     * Get the user list at the server.
     * 
     * @return user list
     */
    public List<String> getUsers() {
        return users;
    }
    
    /**
     * Get the channel list. Channels already created at the server.
     * 
     * @return channel list
     */
    public List<String> getChannels () {
        return channels;
    }
    
}