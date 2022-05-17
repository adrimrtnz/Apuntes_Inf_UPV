//
// Students need not modify nor fully understand this class
//

package utils_jms;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import org.apache.activemq.artemis.api.core.QueueConfiguration;
import org.apache.activemq.artemis.api.core.RoutingType;
import org.apache.activemq.artemis.api.core.SimpleString;
import org.apache.activemq.artemis.api.core.client.ActiveMQClient;
import org.apache.activemq.artemis.api.core.client.ClientMessage;
import org.apache.activemq.artemis.api.core.client.ClientRequestor;
import org.apache.activemq.artemis.api.core.client.ClientSession;
import org.apache.activemq.artemis.api.core.client.ClientSessionFactory;
import org.apache.activemq.artemis.api.core.client.ServerLocator;
import org.apache.activemq.artemis.api.core.management.ManagementHelper;
import org.apache.activemq.artemis.api.core.management.ResourceNames;

//
// Students need not modify nor fully understand this class
//

/**
 * Management utility functions used by ChatServerJMS to control queues at artemis.
 * It uses Artemis Core messages, not JMS.
 * 
 * <p>As a note to implementors, we were using "jolokia" before, but we switched
 * to Artemis core messages.
 * 
 * @author Pablo Galdamez
 */

public class ArtemisCore {


    public ArtemisCore () { }

    /**
     * 
     * Create main queue where this server listens.
     */    
    public void createServerQueue() {
        createQueue ("ChatServer", false);
    }

    
    /**
     * Create a JMS queue at Artemis server, for the specified user.
     * 
     * @param userName user for which queue will be created.
     */
    public void createUserQueue (String userName) {        
        createQueue ("user-" + userName, false);
    }
    
    /**
     * Create a named channel "topic" (a multicast address)
     * 
     * <p>In artemis there is no concept of "topic". It's most equivalent
     * concept is a MULTICAST address. These multicas address can be used
     * as JMS topic when using Artemis as JMS provider.
     *
     * @param name Channel name.
     */
    public void createChannelTopic (String name) {
        createQueue ("channel-" + name, true);
    }

    /**
     * Get the list of channels
     * 
     * @return the list of channels.
     */    
    public List<String> getChannels () {
        List<String> queues = getQueues ();
        List<String> channels = new LinkedList<>();
        
        for (String queueName: queues) {
            if (queueName.startsWith("channel-")) {
                String name = queueName.substring (queueName.lastIndexOf("-") + 1);
                channels.add (name);
            }
        }
        return channels;        
    }

    /**
     * Get the registered users, as the list of queues already created 
     * 
     * @return the registered user list.
     */
    public List<String> getUsers () {        
        List<String> queues = getQueues ();
        List<String> users = new LinkedList<>();
        
        for (String queueName: queues) {
            if (queueName.startsWith("user-")) {
                String name = queueName.substring (queueName.lastIndexOf("-") + 1);
                users.add (name);
            }
        }
        return users;
    }
  
    /**
     * Create a named queue
     * 
     * @param qName queue name
     * @param isMulticast whether multicast (topic) or anycast (queue)
     */    
    private void createQueue (String qName, boolean isMulticast) {
        RoutingType routingType = isMulticast ? RoutingType.MULTICAST : RoutingType.ANYCAST;
        
        QueueConfiguration qc = new QueueConfiguration(qName);
        if (!isMulticast) qc.setMaxConsumers (1); // for "users" and server, maxcount=1
        qc.setRoutingType (routingType);
        
        
        try {
            ServerLocator locator = ActiveMQClient.createServerLocator (InitialContextLoader.getArtemisURL());                
            ClientSessionFactory factory = locator.createSessionFactory();                
            ClientSession session = factory.createSession();
            session.start();

            // Create address and queue.
            session.createAddress (SimpleString.toSimpleString(qName), routingType, true);
            session.createQueue (qc);
            
            session.close();
            
        } catch (Exception e) {
            System.out.println ("Error creating queue: " + e);
        }
    }
    
    
    /**
     * Return all addresses (queues) created at artemis
     * 
     * @return list of addresses
     */
    public List<String> getQueues () {
        List<String> list = new ArrayList<>();
        try {
            ServerLocator locator = ActiveMQClient.createServerLocator (InitialContextLoader.getArtemisURL());                
            ClientSessionFactory factory = locator.createSessionFactory();                
            ClientSession session = factory.createSession();

            session.start();
            
            ClientRequestor requestor = new ClientRequestor(session, "activemq.management");
            ClientMessage message = session.createMessage(false);            
            ManagementHelper.putOperationInvocation(message, ResourceNames.BROKER, "getQueueNames");
                        
            ClientMessage reply = requestor.request(message);
            
            Object []objs = (Object[])ManagementHelper.getResult(reply);
            for (Object obj: objs) {
                list.add( (String) obj);
            }
            
            requestor.close();
            session.close();
            
        } catch (Exception e) {
            System.out.println ("Error reading artemis queues: " + e);
        }

        return list;        
    }

}
