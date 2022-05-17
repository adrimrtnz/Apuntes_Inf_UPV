import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSProducer;
import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.Topic;
import javax.naming.InitialContext;
import utils_jms.ArtemisCore;
import utils_jms.TheInitialContext;
import utils_jms.InitialContextLoader;
import utils_jms.JMSChatConfiguration;
import messages.AMessage;
import messages.MessageFactory;
import messages.ConnectMessage;
import messages.ConnectOkMessage;
import messages.JoinMessage;
import messages.UserLeavesMessage;
import static utils_jms.Destinations.CHANNEL_TOPIC;
import static utils_jms.Destinations.SERVER_QUEUE;
import static utils_jms.Destinations.USER_QUEUE;


/**
 * JMS server for the chat system.
 * 
 * <p>Esentially there should no need for a JMS server, if clients were clever enough
 * to create own queues, and channel topics where already created.
 * 
 * <p> However we include a server to take care of connected users and available channels.
 * This way we forbid same user "nick" to be connected more than once and we can keep
 * track of how many users join to a each channel.
 * 
 * <p>When some user connects for the first time, our server commands "artemis" to create a
 * queue for the user. Notice that we could have engineered our system to allow clients
 * to create own queues. Main advantage of having a dedicated server is to controll how many users
 * are connected at some point, mostly to channels. It is also esier to run the system without a proper
 * authentication / security model, since we have a "central" authority.
 * 
 * <p>Interface for this server are the messages it receives: it processes messages
 * to connect a specific user, and to join channels.
 * 
 * @author Pablo Galdamez
 * @author Agustín Espinosa
 * 
 */
public class ChatServerJMS {

    // Program configuration
    private final JMSChatConfiguration conf;
    
    // Set of functions to command "artemis" to create queues and addresses.
    private final ArtemisCore artemisCore;
    
    // Registered users
    private final Map<String, UserInfo> userMap = new HashMap<>();

    // Registered channels
    private final Map<String, ChannelInfo> channelInfos = new HashMap<>();
    
    // My server queue, where I receive client requess
    private Queue serverQueue;
    
    // Intial context, just to make it easier to create new contexts
    private TheInitialContext tic;
    
    
    /**
     * Creata the main server object.
     * 
     * @param conf server configuration
     */
    
    public ChatServerJMS (JMSChatConfiguration conf) {
        this.conf = conf;        
        this.artemisCore = new ArtemisCore();
    }

    /**
     * ChatServerJMS Initialization routine
     * 
     * <p>Create channels, get already registered users and start the server loop.
     * 
     * @throws Exception Error
     */    
    public void startup () throws Exception {
        
        //
        // We need jndi.properties optionally if there is no URL specified as parameter.
        // Create a context, to interact with the specified URL.
        //
        InitialContext ic = InitialContextLoader.getInitialContext();
        
        // Get connection to "artemis".
        // Connection factory is the common name, both clients and this process share.
        //        
        ConnectionFactory cfac = (ConnectionFactory) ic.lookup("ConnectionFactory");
               
        // Create the first default JMS context
        //
        JMSContext defaultCtx = cfac.createContext();
        
        // Save intial context to be used later
        //
        this.tic = new TheInitialContext (ic, defaultCtx);
        
        // Get the channel list as they exist in artermis now.
        //
        List<String> channelList = artemisCore.getChannels();        

        //
        // If no channels, this is the first time we run our server.
        // create our default channels and create the main server queue.
        //
        if (channelList.isEmpty()) {
            String [] channels = {"Linux", "Spain", "Friends"};
            
            for (String channelName: channels) {
                artemisCore.createChannelTopic (channelName);
            }
            artemisCore.createServerQueue();

            // get again the channel list. Now they must exist.
            channelList = artemisCore.getChannels();
        }
        
        // Now we have channels
        //
        System.out.println("Registered channels: " + channelList);
        
        // Get the named queue where clients connect.
        //
        this.serverQueue = (Queue) ic.lookup (SERVER_QUEUE);

        //
        // For each channel, create channelInfo to keep track of connected users, and
        // then we subscribe to the channel topic messages.
        //
        for (String channelName: channelList) {
            //
            // Create a basic ChannelInfo for the named channel
            channelInfos.put (channelName, new ChannelInfo (channelName));
            
            // Subscribe to channels as topics
            //
            // We'll receive all LEAVE messages so that we can keep channel subscriptors updated
            //
            subscribeTo (channelName);
        }
            
        // Get the list of already-registered users.
        //
        // First time we receive a specific user connection, we tell artemis
        // to create it's queue. This queue for the specified user will 
        // exist forever, until we re-install artemis.
        //
        List<String> userList = artemisCore.getUsers();        
        System.out.println("Registered users: " + userList);
        
        // Keep all users' queues into a map. We'll keep this map updated as new
        // users connect.
        //        
        for (String nick : userList) {
            Queue userQueue = (Queue) ic.lookup (USER_QUEUE + nick);
            userMap.put(nick, new UserInfo (nick, userQueue));
        }
        
        // Finally run the main server "forever", processing messages as they arrive in.
        runServerLoop ();
    }

    /**
     * Run the ChatServerJMS loop.
     * 
     * <p> The loop iterates forever, waiting for a message and processing it.
     * 
     * <p> Notice there is no need to implement a server like this. We could have implemented
     * it as an asynchronous message listener. This implementation allows studets to analize
     * different alternatives.
     * 
     * @throws Exception Error
     */
    private void runServerLoop () throws Exception {
        
        // Create my own Context.
        //
        JMSContext ctx = tic.newContext();

        // Create a consumer for my queue
        //
        JMSConsumer cons = null;
        try {
            cons = ctx.createConsumer (serverQueue);
        } catch (Exception e) {
            // Main queue should be configured with "maxCounsumers" set to 1.
            // We can confirm this point using Artemis console.
            //
            System.out.println ("ERROR ==> Cannot create server consumer. Some other ChatServerJMS is running for same Artemis.");
            return; // we end here.
        }

        // This server is a classic "while(true)" server.
        // Receive a client request, and serve it.
        
        while (true) {
            
            // Wait for a new client request.
            //
            System.out.println("Waiting for client messages...");
            ObjectMessage msg = (ObjectMessage) cons.receive();
            
            //
            // Get the message content            
            AMessage bmsg = (AMessage) msg.getObject();
            System.out.println ("OK ==> We received a message of type: " + bmsg.getType());
            
            switch (bmsg.getType()) {
                
                case CONNECT: {
                    ConnectMessage cm = (ConnectMessage) bmsg;
                    onConnect (cm, msg.getJMSReplyTo());
                    break;
                }
                case JOIN: {
                    JoinMessage jm = (JoinMessage) bmsg;
                    onJoin (jm, msg.getJMSReplyTo());
                    break;
                }
                
                default: {                    
                    System.out.println("Unknown message type: " + bmsg.getType());
                    break;
                }
            }            
        }        
    }
    
    /**
     * Process a ChatClientJMS request to connect.
     * 
     * <p> to process it, take note on the user, create it's queue if it didn't exist, and
     * reply to the client with the channel list found at the server.
     * 
     * @param msg Connect message
     * @param replyTo Where client waits for a reply.
     * 
     * @throws Exception Errors
     */
    private void onConnect (ConnectMessage msg, Destination replyTo) throws Exception
    {
        // Create specialized context and producer to send our reply.
        //
        JMSContext ctx = tic.newContext();
        JMSProducer prod = ctx.createProducer();
        
        // We received a CONNECT message. Get its username                    
        //
        String userName = msg.getNick();
        if (userName.equals("")) {
            System.out.println("New anonimous connection. Ignored.");
            ctx.close();
            return;
        }

        System.out.println("OK ==> accepted CONNECT request from user " + userName);
            
        // Get user info for this user. If not found, user is completely new
        //
        UserInfo uinfo = userMap.get(userName);        
        if (uinfo == null) {
            
            // Brand new user: create new queue for it
            //
            artemisCore.createUserQueue (userName);
                
            // Get the queue and create the user info data. User is online now.
            //
            Queue userQueue = (Queue) tic.ic().lookup (USER_QUEUE + userName);
            
            // Set uinfo to the newly created user
            uinfo = new UserInfo (userName, userQueue);
            userMap.put(userName, uinfo);
                
        } 
        
        // Keep this variable to allow/forbid this client connection.
        //
        boolean allowConnection = true;
        
        //
        // Now that we are sure that user queue exist, create a temporary consumer on it.
        //
        // This trick allows us to check if there's already a ChatClientJMS using same 
        // nick and already connected.
        // Queue must be created with "maxConsumers=1"
        //
        try {
            JMSConsumer cons = ctx.createConsumer ( uinfo.queue() );
            // If consumer was created without throwing an exception, means there's 
            // no other client using this queue. Then we allow client to connect.
            // Now close this temporary queue.
            cons.close(); 
        } catch (Exception e) {
            // On exception, we don't allow connection.
            allowConnection = false;     
        }
        
        // Prepare a reply to the connect message
        //
        ObjectMessage reply = ctx.createObjectMessage ();
        ConnectOkMessage okMsg;
        
        if (allowConnection) {
            
            // allow connection OK
            //
            okMsg = MessageFactory.connectOkMessage (userMap.keySet(), channelInfos.keySet());
            
        } else {
            
            // If user already existed and is online, we don't allow duplicate "nick" connection.
            //
            okMsg = MessageFactory.connectOkMessage (null, null);
            
        }                
        
        // Set the reply object.
        //
        reply.setObject (okMsg);
        
        // Send the reply
        //
        try {
            prod.send(replyTo, reply);
        } catch (Exception e) {
            System.out.println("OK ==> CONNECT from user " + userName + " was OLD!");            
            //
            // TAG: XYZABC
            // See method callServerConnect at ChatClientJMS, with tag XYZABC
            //
            // If we cannot send a reply to ChatClientJMS, is probably because it already closed
            // its temporary queue. If this happens, it's also likely that client sent this message to
            // us long time ago, and maybe even disconnected. 
            //
            // Since it's a stale request, we don't need to do anything at all.
            // Client will connect again, if ever.            
        }
        
        // close this context            
        //
        ctx.close();
    }

    /**
     * Process a JOIN message from a ChatClientJMS
     * 
     * <p> To process the join, reply this user with the list of current users at said channel.
     * After sending the reply, broadcast to the channel itself the new JOIN
     * 
     * @param msg Join message
     * @param replyTo where to reply
     * @throws Exception Errors
     */
    private void onJoin (JoinMessage msg, Destination replyTo) throws Exception
    {
        // Create a specialized context
        //
        JMSContext ctx = tic.newContext();
        JMSProducer prod = ctx.createProducer();
        
        // 
        // We just received a JOIN request. Get its nick and channelName
        //
        String nick = msg.getNick();        
        String chan = msg.getChannelName();
        
        System.out.println("User " + nick + " requests to join " + chan);
        
        // Save new user into Channel
        //
        channelInfos.get (chan).addUser (nick);
        
        // Get the updated channel user list
        //
        List<String> users = channelInfos.get(chan).getUsers();        
        System.out.println ("Send list of users for channel: " + chan + ": " + users);
        
        // Build reply for the requestor
        //
        ObjectMessage reply = ctx.createObjectMessage (MessageFactory.joinOkMessage(chan, users) );
        prod.send(replyTo, reply);
        
        // Now broadcast to "topic" channel about the new user
        //
        Topic topic = (Topic) tic.ic().lookup (CHANNEL_TOPIC + chan);
        prod.send(topic, ctx.createObjectMessage(MessageFactory.userJoinsMessage(nick)));
        
        // close this context            
        //
        ctx.close();
    }
            
            
    /**
     * Subscribe to all channel messages.
     * 
     * <p> As of now we are only interested on USER_LEAVES messages
     * 
     * @param channelName channel to monitor
     * @throws Exception 
     */
    private void subscribeTo (String channelName) throws Exception {        
        //
        // Create a consumer for this topic
        //
        Topic top = (Topic) tic.ic().lookup(CHANNEL_TOPIC + channelName);
        JMSContext ctx = tic.newContext();
        JMSConsumer cons = ctx.createConsumer(top);
                
        // Install the asynchronous listener
        //
        cons.setMessageListener(new MessageListener() {
            @Override
            public void onMessage(Message msg) {                
                try {
                    onMessageEx (msg);
                } catch (Exception e) {
                    System.err.println ("Server exception when reading messages: " + e);
                }
            }
            public void onMessageEx (Message msg) throws Exception {
                 AMessage bmsg = (AMessage) ((ObjectMessage) msg).getObject();
                 switch (bmsg.getType()) {
                     case USER_LEAVES: {
                         UserLeavesMessage jmsg = (UserLeavesMessage) bmsg;
                         System.out.println ("User " + jmsg.getNick() + " leaves channel " + channelName);
                         channelInfos.get(channelName).removeUser (jmsg.getNick());
                         break;
                     }
                         
                 }
            }
        });
    }

    /**
     * 
     * Simple class to keep track on connected/registered users
     */
    private static class UserInfo {

        private final Queue queue;
        private final String nick;
        private boolean isOnline;

        private UserInfo (String nick, Queue queue) {
            this.nick = nick;
            this.queue = queue;
            this.isOnline = false;
        }
        private boolean isOnline() {return isOnline;}
        private UserInfo setOnline (boolean online) {this.isOnline = online; return this;}
        private Queue queue() {return queue;}
    }
    
    
    /**
     * Simple class to keep track of how many users are in a channel.
     * 
     * Notice it is synchronized, since listeners run in own thread, and we 
     * access this object from the main thread.
     * 
     */
    private static class ChannelInfo {
        private final String channelName;
        private final List<String> users;
        
        public ChannelInfo (String channelName) {
            this.channelName = channelName;
            this.users = new LinkedList<>();
        }
        
        public synchronized ChannelInfo addUser (String nick) {
            users.add(nick);
            return this;
        }
        public synchronized ChannelInfo removeUser (String nick) {
            users.remove (nick);
            return this;
        }
        public synchronized List<String> getUsers () {
            List<String> copy = new ArrayList<>(users.size());
            copy.addAll(users);
            return copy;
        }
    }
    
    
    /**
     * ChatServerJMS main program
     * 
     * <p>Load configuration parameters from command line, create a new 
     * ChatServerJMS object and start it.
     * 
     * @param args command line arguments
     */
    
    public static void main(final String[] args) {
        
        JMSChatConfiguration conf = JMSChatConfiguration.parse(args);
        System.out.println ("url: " + conf.getArtemisUrl());        
        InitialContextLoader.setDefaultArtemisURL (conf.getArtemisUrl());
        
        ChatServerJMS server = new ChatServerJMS (conf);

        try {        
            server.startup();
        } catch (Exception e) {
            System.err.println ("Error in server ==> Is Artemis running??");
            System.err.println ("Exception ==> " + e);
            e.printStackTrace (System.err);
            System.exit(-1);
        }
    }

    
}
