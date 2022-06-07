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
import messages.JoinMessage;
import messages.UserJoinsMessage;
import messages.UserLeavesMessage;
import utils_jms.InitialContextLoader;
import utils_jms.JMSChatConfiguration;
import static utils_jms.Destinations.CHANNEL_TOPIC;
import static utils_jms.Destinations.SERVER_QUEUE;
import static utils_jms.Destinations.USER_QUEUE;


/**
 * ChatRobot program built using JMS
 * 
 * Similar to ChatClientJMS but without graphical interface 
 * Connects to a specific channel
 * Keeps in a loop (similar to ChatServerJMS) to process messages that arrive to the channel
 * and in case of JOIN messages, sends a welcome message to the channel
 *
 * @author Ana- versión básica sin comprobación de errores
 */

public class ChatRobot {

  public static void main (String[] args) {

	JMSChatConfiguration  conf; // Our initial configuration
	final String nick;          // Our nick name
	String myChannelName;      // Channel name to which we connect
	InitialContext ic;
	ConnectionFactory cfac;
	JMSContext ctx;
	JMSProducer producer;
	JMSConsumer consumer;

	Queue serverQueue;         // Queue where we send messages to ChatServerJMS
	Queue myQueue;             // Our queue where we receive private messages      
	Topic channelTopic;       // TOPIC channel where we receive the messages send to the channel

    conf = JMSChatConfiguration.parse(args);
	if (conf.getNick() == null) nick = "ChatRobot"; else nick = conf.getNick();  //default nick
    if ((myChannelName=conf.getChannelName()) == null) myChannelName = "Spain"; //default channel
	String serverUrl = conf.getArtemisUrl(); 
    System.out.println("OK ==> 'ChatRobotJMS' running. Using artemis at " + serverUrl); 
    System.out.println("ChatRobot JMS: tries to connect to: " + serverUrl + " nick =" + nick + " channel=" + myChannelName);

    try {   
	    InitialContextLoader.setDefaultArtemisURL (serverUrl);   
	    ic = InitialContextLoader.getInitialContext(); // Create the JMS initial context

        //STEP 1: Connection to Artemis and getting the server queue. 
	    //1a. COMPLETE: Connect to Artemis, using the connection factory named "ConnectionFactory"
	   cfac = (ConnectionFactory) ic.lookup("ConnectionFactory");



	    //1b. COMPLETE: Create a JMS context
		try {
			ctx = cfac.createContext();
		} catch (Exception e) {
			throw new Exception("Cannot contact Artemis at url: " + serverUrl);
		}
        
		//1c. COMPLETE: Obtain the queue of our ChatServer application. Its name is stored in the SERVER_QUEUE constant. 
		//This constant is declared at Destinations class (in utils_jms package)
		serverQueue = (Queue) ic.lookup(SERVER_QUEUE);

	    // STEP 2: Now we will send a "connect" message to the server  

	    //2.a COMPLETE: Create a producer
		producer = ctx.createProducer();
	 
	    //2.b COMPLETE: Create an object message, using the message factory to construct a "connectMessage"
		Message msg = ctx.createObjectMessage(MessageFactory.connectMessage(nick));

	    //2.c COMPLETE: Create a temporary queue for receiving server's answer
		Queue tempQueue = (Queue) ctx.createTemporaryQueue();

	    //2.d COMPLETE: Assign the "replyTo" property to this temporary queue
	    msg.setJMSReplyTo(tempQueue);

	    //2.e COMPLETE: Send the message to the queue, using the producer. 
		try {
			producer.send(serverQueue, msg);
		} catch (Exception e) {
			ctx.close();
            throw new Exception ("Cannot send message to ChatServerJMS queue");
		}

        //2.f COMPLETE: Create a consumer for our temporary queue
		consumer = ctx.createConsumer(tempQueue);

        //2.g COMPLETE: Consumer waits the reception of a message. 
        // If everything is ok, the private queue of the user has been created (users-MYNAME) and ChatServer has sent a "ConnectOKMessage" to our
        // temporary queue. 
        //Optionally, we can read this message and get users list and channels list. 
		ObjectMessage m = (ObjectMessage) consumer.receive(1000);

		if (m == null) {
			consumer.close();
			ctx.close();
			throw new Exception ("ChatServerJMS not responding.");
		}

        //ACTIVITY 5: OPTIONAL
	    // listen from my private queue and answer "i am a bot"  
		// we need a second context because Artemis uses ThreadPoolExecutor 
		// when installing the MessageListener, for the asynchronous message reading  
		// We will set a new MessageListener that implements the onMessage method. 
		



	    // STEP 3: Join a channel and send a welcome message
	    //3.a COMPLETE: create a Join message. Set the temporary queue as the replying queue
	   	Message joinMsg = ctx.createObjectMessage(MessageFactory.joinMessage(myChannelName, nick));
		joinMsg.setJMSReplyTo(tempQueue);

	    //3.b COMPLETE: send the join message to the ChatServer queue
		producer.send(serverQueue, joinMsg);

	    //3.c Obtain the channel TOPIC
	    channelTopic = (Topic) ic.lookup (CHANNEL_TOPIC + myChannelName);

      	//3.d ChatRobot sends a welcome message to the channel
		String welcomeMsg = "Hi there, I'm a Robot";
		producer.send(channelTopic, ctx.createObjectMessage(MessageFactory.chatMessage(nick, welcomeMsg)) );
	    

	    // STEP 4: Finally run the ChatRobot "forever", processing messages as they arrive in the channel
	    //4.a Create a consumer for the channel queue
		JMSConsumer channelConsumer = ctx.createConsumer(channelTopic);

	    while (true) {
			System.out.println("Waiting for clients to join ...");

			//4.b The consumer waits for a message. 
			ObjectMessage message = (ObjectMessage) channelConsumer.receive();
			AMessage bmsg = (AMessage) message.getObject();


			//4.c In case of receiving a USER_JOINS message, we send a greeting message to the channel, saying "hello" to the user that has just joined
			switch(bmsg.getType()) {
				case USER_JOINS:
				    UserJoinsMessage jm = (UserJoinsMessage) bmsg;
					producer.send(channelTopic, ctx.createObjectMessage(MessageFactory.chatMessage( jm.getNick(), "Welcome " + jm.getNick())));
					System.out.println("USER_JOINS");
				break;
				default:
					System.out.println("SWITCH: " + bmsg.getType().toString());
			}
			      
        }	
    } catch (Exception e) {
        System.err.println ("Error in ChatRobot: " + e);
        e.printStackTrace (System.err);
        System.exit(-1);
    }
  }
}
