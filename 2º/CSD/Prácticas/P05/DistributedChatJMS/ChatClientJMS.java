
import ui.ChatClientFace;
import ui.ChatUIFace;
import java.util.List;
import javax.jms.ConnectionFactory;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSProducer;
import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.Topic;
import javax.naming.InitialContext;
import messages.AMessage;
import messages.ChatMessage;
import messages.MessageFactory;
import messages.ConnectOkMessage;
import messages.JoinOkMessage;
import messages.UserJoinsMessage;
import messages.UserLeavesMessage;
import ui.ChatUI;
import utils_jms.InitialContextLoader;
import utils_jms.JMSChatConfiguration;
import utils_jms.TheInitialContext;
import utils.SynchroMap;
import static utils_jms.Destinations.CHANNEL_TOPIC;
import static utils_jms.Destinations.SERVER_QUEUE;
import static utils_jms.Destinations.USER_QUEUE;


/**
 * Chat client program built using JMS
 * 
 * <p> It implements ChatClientFace, so that it can work with ChatUIFace graphical interfaces.
 *
 * @author Pablo Galdamez
 */
public class ChatClientJMS 
        implements ChatClientFace 
{

    // Our initial configuration
    private final JMSChatConfiguration conf;
    
    // The User interface
    private ChatUIFace ui;
    
    // Initial context
    private TheInitialContext tic; 
    
    // Our nick name
    private String nick;

    // Queue where we send messages to ChatServerJMS
    //
    private Queue serverQueue;
        
    // My own queue where I receive messages sent to me.
    //
    private Queue myQueue;
        
    // Channel listeners
    // We keep a listener for each channel I join.
    // This listeners can be cancelled when I leave the channel.
    //
    private SynchroMap<String, DestinationListener> channelSubscriptions = new SynchroMap<>();
    
    // My own listener information. I'll receive my own messages here.
    //
    private DestinationListener myListener;
    
    /**
     * Create a ChatClientJMS program.
     * 
     * @param conf configuration
     */    
    private ChatClientJMS (JMSChatConfiguration conf) {
        this.conf = conf;
        
        // Clean shutdown on any situation (except computer crash, of course)
        Runtime.getRuntime().addShutdownHook( new Thread ( () -> {
            doDisconnect();
        }));
    }

    /**
     * Install UI to use
     * 
     * @param ui the ui
     */    
    private void setUI (ChatUIFace ui) {
        this.ui = ui;
    }

    
    //
    // ISA ChatClientFace    
    //

    /**
     * Connect to our ChatServerJMS
     * 
     * <p> Connect means to send a CONNECT message to the server and wait for reply.
     * <p> Once connected, register a listener to our own queue to receive private 
     * messages.
     * 
     * @param serverUrl server url where artemis runs
     * @param nick Our nick name
     * 
     * @return List of channels as server returns
     * @throws Exception Erros
     */
    @Override
    public String[] doConnect (String serverUrl, String nick) throws Exception {
        try {
            return doConnectEx (serverUrl, nick);
        } catch (Exception e) {
            if (tic != null) tic.close();
            throw e; // rethrow
        }
    }


    //
    // This is the real "doConnect". It possibly throws an Exception.
    // doConnect calls this method, catching the exception so that it can close
    // the default context, if it was open, but complete connection didn't succeed.
    //
    private String[] doConnectEx (String serverUrl, String nick) throws Exception {
        
        // Save my user name
        //
        this.nick = nick;
        
        // Sanity check on ServerURL
        //
        String url = JMSChatConfiguration.normalizeUrl(serverUrl);
        if (url == null) {
            throw new Exception ("Wrong URL: " + serverUrl);
        } else serverUrl = url;
        
        //
        // Save the user-provided serverUrl as the current artemis URL
        //
        InitialContextLoader.setDefaultArtemisURL (serverUrl);
        
        // 
        // Create the JMS initial context
        InitialContext ic = InitialContextLoader.getInitialContext();
        
        // Connect using same connection factory as other clients and the server do.
        //
        ConnectionFactory cfac = (ConnectionFactory) ic.lookup("ConnectionFactory");
        
        // Create a default JMS context.
        // This is where we really contact Artemis
        //
        JMSContext defaultContext;
        try {
            defaultContext = cfac.createContext();
        } catch (Exception e) {
            throw new Exception ("Cannot contact Artemis at url: " + serverUrl);
        }
        
        // Save initial context to be used later
        // We use this initial context information to create new contexts and to
        // close connection later.
        //
        this.tic = new TheInitialContext (ic, defaultContext);
                
        // Get server queue and keep it as a global, since we use it often
        //
        this.serverQueue = (Queue) ic.lookup (SERVER_QUEUE);
        
        // Call server to connect and get its channel list
        String [] channels = callServerConnect ();

        // Once I succseefilly connect to the server, I'm sure there's a queue for me.
        // Get my own queue and keep it as a global, since we use it often
        this.myQueue = (Queue) ic.lookup (USER_QUEUE + nick);        

        // Install an asynchronous handler to receive any messages delivered to me
        //
        this.myListener = listenMyMessages ();        

        // Finally return the list of channels as mandated by interface ChatClientFace.
        return channels;
    }

    /**
     * Send a connect message to ChatServerJMS and wait for reply.
     * 
     * @return list of channels at the server
     * 
     * @throws Exception Error
     */
    private String [] callServerConnect () throws Exception {
        
        // Create a new specific context for this request (thread-safe)
        //
        JMSContext ctx = tic.newContext();
        
        // Create a producer. Queue will be bound when we send messages
        //
        JMSProducer producer = ctx.createProducer();
        
        // Build a message. This is the first message we send to the server.
        // It must be of type "ConnectMessage"
        //
        Message msg = ctx.createObjectMessage (MessageFactory.connectMessage(nick));
                
        // Create a temporary queue to receive server reply
        //
        Queue tempQueue = (Queue) ctx.createTemporaryQueue();
        
        // To let our server know where to reply, we set the "replyTo" property.
        //
        msg.setJMSReplyTo (tempQueue);
                
        // Send the message            
        //
        try {
            producer.send (serverQueue, msg); 
        } catch (Exception e) {
            // The most likely reason is that queue does not exist. Meaning, it ChatServerJMS never
            // run after installing Artemis.
            ctx.close();
            throw new Exception ("Cannot send message to ChatServerJMS queue");
        }
        
        // We always need to create a consumer to receive from a given destination.
        // We create a consumer for this temporary queue
        //
        JMSConsumer consumer = ctx.createConsumer (tempQueue);
        
        // We wait for this message. This is a synchronous wait. We don't
        // proceed until server confirms connection.
        //
        // We just wait for 1 second. If server is not online, we cannot continue.
        //
        ObjectMessage m = (ObjectMessage) consumer.receive(1000);
        consumer.close(); // Free up resources for this temporary queue.
        
        // If we received no answer, ChatServerJMS is not online.
        if (m == null) {
            // TAG: XYZABC
            // ChatServerJMS won't be able to answer us anymore.
            // See comment tagged "XYXABC" at ChatServerJMS, method "onConnect".
            consumer.close();   
            ctx.close();
            throw new Exception ("ChatServerJMS not responding.");
        }
        
        // Get the message contents.
        //
        ConnectOkMessage myobject = (ConnectOkMessage) m.getObject();

        // Get list of channels from the message contents.
        //
        List<String> channels = myobject.getChannels();
        
        // Server didn't allow connection, if channel list is empty.
        //
        if (channels.isEmpty()) {
            ctx.close();
            throw new Exception ("Server denied connection. Possible nick duplicate.");
        }
                
        // Finally we return the list of channels.
        //
        return channels.toArray (new String [channels.size()]);        
    }

    /**
     * Install an asynchronous listener to receive all messages sent to my own queue
     * 
     * <p> as of now, we just receive CHAT_MESSAGE messages
     */
    private DestinationListener listenMyMessages () {        
        //
        // Create a consumer for my queue
        //
        JMSContext ctx = tic.newContext();
        JMSConsumer cons = ctx.createConsumer (myQueue);
        
        // create my listener. It is "closable", closing my consumer and context.
        //
        DestinationListener lis = new DestinationListener (ctx, cons);
        
        cons.setMessageListener(new MessageListener() {
            
            @Override
            public void onMessage(Message msg) {                
                try {
                    onMessageEx (msg);
                } catch (Exception e) {
                    System.err.println ("Exception when reading messages: " + e);
                }
            }

            /**
             * Process a message that arrives asynchronously
             * 
             * @param msg message.
             * @throws Exception Error
             */            
            
            public void onMessageEx (Message msg) throws Exception {
                 AMessage bmsg = (AMessage) ((ObjectMessage) msg).getObject();
                 
                 switch (bmsg.getType()) {
                     
                     case CHAT_MESSAGE: {
                         // 
                         // Get the message and show it into the UI
                         //
                         ChatMessage chat = (ChatMessage) bmsg;
                         ui.showPrivateMessage (chat.getSource(), nick, chat.getLine());
                         break;
                     }
                         
                 }
            }
        });
        
        return lis;
        
    }
    
    
    /**
     * Install a listener to receive all messages delivered to a channel
     * 
     * @param channelName channel name
     * @throws Exception Errors
     */
    private void subscribeToChannel (String channelName) throws Exception {
        //
        // Create a consumer for the channel topic
        //
        Topic top = (Topic) tic.ic().lookup (CHANNEL_TOPIC + channelName);
        JMSContext ctx = tic.newContext();
        JMSConsumer cons = ctx.createConsumer(top);

        //
        // Save channel subscription so that we can close later, on Leave.
        //
        channelSubscriptions.put(channelName, new DestinationListener (ctx, cons));

        // Install aynchronous message listener for incomming channel messages.
        //        
        cons.setMessageListener(new MessageListener() {
            @Override
            public void onMessage(Message msg) {                
                try {
                    onMessageEx (msg);
                } catch (Exception e) {
                    System.err.println ("Exception when reading messages: " + e);
                }
            }
            
            //
            // We receive JOIN/LEAVE notifications and CHAT_MESSAGEs
            // Effect is to show it all at the user interface.
            //
            public void onMessageEx (Message msg) throws Exception {
                 AMessage bmsg = (AMessage) ((ObjectMessage) msg).getObject();
                 switch (bmsg.getType()) {
                     case CHAT_MESSAGE: {
                         ChatMessage cm = (ChatMessage) bmsg;
                         ui.showChannelMessage(cm.getSource(), channelName, cm.getLine());
                         break;
                     }
                     case USER_JOINS: {
                         UserJoinsMessage jm = (UserJoinsMessage) bmsg;
                         ui.showUserEntersChannel(channelName, jm.getNick());                         
                         break;
                     }
                     case USER_LEAVES: {
                         UserLeavesMessage lm = (UserLeavesMessage) bmsg;
                         ui.showUserLeavesChannel(channelName, lm.getNick());                         
                         break;
                     }
                     default:
                         System.out.println ("Unknown message: " + bmsg.getType());
                     
                 }
            }
        });
    }
            
    /**
     * Disconnect from the server.
     * 
     * <p> To disconnect, leave all channels, close my own listener and close initial context.
     * <p> This call is idempotent.
     */
    
    @Override
    public void doDisconnect() {
        try {
            leaveAllChannels();
            if (myListener != null) myListener.close();
            myListener = null;
            if (tic != null) tic.close();
            tic = null;
        } catch (Exception e) {}
        
    }
    
    //
    // ISA ChatClientFace
    //
    
    /**
     * Leave a channel 
     * 
     * <p>In out systemn, leave means to broadcast a message to the channel "topic"
     * and to close our channel listener (our subscription)
     * 
     * @param channelName channel to leave
     * @throws Exception Error
     */
    @Override
    public void doLeaveChannel(String channelName) throws Exception {
        //
        // Stop our listener
        //
        channelSubscriptions.get (channelName).close();
        channelSubscriptions.remove (channelName);
        
        // Broadcast the LEAVE message
        //
        JMSContext ctx = tic.newContext();
        JMSProducer prod = ctx.createProducer();
        Topic topic = (Topic) tic.ic().lookup (CHANNEL_TOPIC + channelName);
        prod.send(topic, ctx.createObjectMessage ( MessageFactory.userLeavesMessage(nick)));
        ctx.close();        
    }

    //
    // ISA ChatClientFace
    //
    
    /**
     * Sending a Join message to the ChatServerJMS and wait for reply.
     * 
     * <p> before asking the server, subscribe to the channel messages.
     * 
     * @param channelName channel to join
     * 
     * @return list of users that are already connected to this channel
     * @throws Exception Error
     */
    @Override
    public String[] doJoinChannel(String channelName) throws Exception {

        //
        // We start subscribing to the channel, so that we get our own JOIN message as 
        // the server broadcasts our addition.
        //
        subscribeToChannel (channelName);

        // Create new context for this request
        //        
        JMSContext ctx = tic.newContext();
        JMSProducer prod = ctx.createProducer();
        
        // Create a temporary queue to receive server reply
        //
        Queue tempQueue = (Queue) ctx.createTemporaryQueue();
        
        // Create message of type Join 
        //
        Message msg = ctx.createObjectMessage( MessageFactory.joinMessage (channelName, nick)) ;
        
        // To let the server know where to reply. We set the "replyTo" property.
        //
        msg.setJMSReplyTo (tempQueue);

        // Send the message        
        //
        prod.send(serverQueue, msg);

        // Wait blocking to receive the message
        //
        JMSConsumer cons = ctx.createConsumer (tempQueue);
        ObjectMessage reply = (ObjectMessage) cons.receive();
        
        // Get data from reply. It must be a JoinOK message.
        // As of now, server doesn't forbid us.
        //
        JoinOkMessage joinOk = (JoinOkMessage) reply.getObject();
        
        // Get the user list from server reply.
        //
        List<String> users = joinOk.getUsers();        
        
        //
        // If server would deny us joining. We could check here if user list is empty.        
        //
        
        // Close this context
        //
        cons.close();
        ctx.close();
        
        // Return the user list
        return users.toArray(new String [users.size()]);
    }

    
    /**
     * Send a channel message
     * 
     * @param dst channel name
     * @param msg message to send
     * @throws Exception errors while sending the message
     */    
    @Override
    public void doSendChannelMessage(String dst, String msg) throws Exception {
        // 
        // Our server implementation has no control on who sends a channel message.
        //
        // Actually, anyone, even the Artemis Console itself could send a message.
        // Security concerns should be considered into Artemis configuration, more
        // than here.
        //
        // Having said that, now we refuse sending messages if we didn't join this channel.
        //
        // An alternative would be to send messages always to the server and let the server
        // be the one who broadcasts channel messages, controlling who sends.
        //
        // We decided to broacast messages directly, to let students practice more with
        // the idea of "topics" and it's possibilities.
        //
        if (channelSubscriptions.get(dst) == null) {
            throw new Exception ("Join channel before sending messages");
        }        
        
        // Broadcast the message
        //
        JMSContext ctx = tic.newContext();
        JMSProducer prod = ctx.createProducer();
        Topic topic = (Topic) tic.ic().lookup (CHANNEL_TOPIC + dst);
        prod.send(topic, ctx.createObjectMessage ( MessageFactory.chatMessage(nick, msg)));
        ctx.close();
    }

    /**
     * Send a message to a specific user
     * 
     * <p> To do so, just send a CHAT_MESSAGE to the destination queue
     * 
     * @param dst user destination of the messae
     * @param msg the message
     * @throws Exception error
     */
    @Override
    public void doSendPrivateMessage(String dst, String msg) throws Exception {
        JMSContext ctx = tic.newContext();
        JMSProducer prod = ctx.createProducer();
        Queue queue = (Queue) tic.ic().lookup(USER_QUEUE + dst);
        prod.send (queue, ctx.createObjectMessage ( MessageFactory.chatMessage(nick, msg)));
        ctx.close();
    }

    //
    // Leave all channels. Notice we use a copy, to avoid concurrentModificationException
    //
    private void leaveAllChannels () throws Exception {        
        for (String channelName: channelSubscriptions.copyOf().keySet()) {
            doLeaveChannel (channelName);
        }
    }
    
    /**
     * Terminate this program.
     * 
     * To make server life easier. We leave all channels and disconnect.
     * 
     */
    @Override
    public void doTerminate() {
        doDisconnect ();
        System.exit(0);
    }

    /**
     * Simple class to hold queue/topic listener info, so that we can close it
     * when user leaves a channel or disconnects
     */
    private static class DestinationListener {
        private JMSConsumer cons;
        private JMSContext ctx;
        private DestinationListener (JMSContext ctx, JMSConsumer cons) {
            this.ctx = ctx;
            this.cons = cons;
        }
        private void close () {
            cons.close();
            ctx.close();
        }
    }

    
    /**
     * Main client program
     * 
     * <p>It creates the Client object, and shows the graphical interface.
     * 
     * <p>Everything that happens from now on will be commanded by the graphical interface.
     * 
     * <p>Graphical interface will call our methods as speficied at ChatClientFace.java
     * 
     * @param args command line parameters
     */
    public static void main (String[] args) {
         ChatClientJMS cc = new ChatClientJMS (JMSChatConfiguration.parse(args));
         ChatUI ui = new ChatUI (cc, "Chat Client JMS", cc.conf.getArtemisUrl(), cc.conf.getNick(), cc.conf.getChannelName());
         cc.setUI (ui);
         ui.show();        
         System.out.println("OK ==> 'ChatClientJMS' running. Using artemis at " + cc.conf.getArtemisUrl());        
     }

}
