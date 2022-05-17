package messages;

import static messages.AMessage.ChatMessageType.CHAT_MESSAGE;

/**
 * Message sent from ChatClientJMs to other users or to channels when
 * chatting.
 * 
 * @author Pablo Galdamez
 */
public class ChatMessage extends AMessage {
    
    private final String src;
    private final String line;
    
    /**
     * Build a new chat message 
     * 
     * @param src Sender
     * @param line message text
     */
    public ChatMessage (String src, String line) {
        super (CHAT_MESSAGE);
        this.line = line;
        this.src = src;
    }

    /**
     * Get the message contents
     * 
     * @return the message text
     */
    public String getLine() {
        return line;
    }

    /**
     * Get the message sender
     * 
     * @return message source
     */
    public String getSource() {
        return src;
    }
}
