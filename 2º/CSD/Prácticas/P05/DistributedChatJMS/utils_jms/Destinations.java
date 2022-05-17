package utils_jms;

/**
 *
 * Destination names
 * 
 * @author Pablo Galdamez
 */
public interface Destinations {
    public static final String SERVER_QUEUE = "dynamicQueues/ChatServer";
//    public static final String SERVER_QUEUE = "dynamicQueues/csd";
    public static final String USER_QUEUE = "dynamicQueues/user-";
    public static final String CHANNEL_TOPIC = "dynamicTopics/channel-";    
}
