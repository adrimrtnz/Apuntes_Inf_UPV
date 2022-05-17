package messages;

import java.util.Collection;
import java.util.List;

/**
 * Simple factory for our messages.
 * 
 * <p>Factory is not really needed. It just helps autocomplete facilities of IDEs
 * 
 * @author Pablo Galdamez
 */

public class MessageFactory {
    public static ConnectMessage connectMessage (String nick) {
        return new ConnectMessage (nick);
    }
    
    public static ConnectOkMessage connectOkMessage (Collection<String> users, Collection<String> channels) {
        return new ConnectOkMessage (users, channels);
    }
    
    public static JoinMessage joinMessage (String channelName, String nick) {
        return new JoinMessage (channelName, nick);
    }
    
    public static JoinOkMessage joinOkMessage (String channelName, List<String> users) {
        return new JoinOkMessage (channelName, users);
    }
    
    public static UserJoinsMessage userJoinsMessage (String nick) {
        return new UserJoinsMessage (nick);
    }
    
    public static UserLeavesMessage userLeavesMessage (String nick) {
        return new UserLeavesMessage (nick);
    }
    
    public static ChatMessage chatMessage (String src, String txt) {
        return new ChatMessage (src, txt);
    }
}
