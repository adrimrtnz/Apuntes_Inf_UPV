//
// This file must be implemented when completing "ChatRobot activity"
//

import utils_rmi.ChatConfiguration;
import utils_rmi.RemoteUtils;
import faces.IChatMessage;
import faces.MessageListener;
import impl.ChatMessageImpl;
import impl.ChatUserImpl;

import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.*;
import java.util.*;

import faces.INameServer;
import faces.IChatServer;
import faces.IChatChannel;
import faces.IChatUser;

/**
 * ChatRobot implementation
 * 
 * <p> Notice ChatRobot implements MessageListener. MUST not extend ChatClient.
 * 
 */

public class ChatRobot implements MessageListener
{

    private ChatConfiguration conf;
    private IChatUser botUser = null;
    private IChatServer srv = null;

    public ChatRobot (ChatConfiguration conf) {
        this.conf = conf;
    }
    
   @Override
   public void messageArrived (IChatMessage msg) {
       //*****************************************************************
       // Activity: implement robot message processing
       
   }
   
   private void work () throws Exception {
       
       String channelName = conf.getChannelName();
       if (channelName == null) channelName = "#Linux";
       System.out.println ("Robot will connect to server: '" + conf.getServerName() + "'" + 
               ", channel: '" + channelName + "'" + 
               ", nick: '" + conf.getNick() + "'" +        
               ", using name server: '" + conf.getNameServerHost() + ":" + conf.getNameServerPort() + "'");
       
       try {
           //*****************************************************************
           // Activity: implement robot connection and joining to channel
           INameServer reg = INameServer.getNameServer(conf.getNameServerHost(), conf.getNameServerPort());
           System.out.println(RemoteUtils.remote2String(reg));
           
           srv = (IChatServer) reg.lookup(conf.getServerName());
           System.out.println(RemoteUtils.remote2String(srv));
           
       } catch (Exception e) {
           System.out.println("Something went wrong: " + e);
       }

       // if we didn't find it, raise exception
       if (srv == null) throw new Exception ("Server '" + conf.getServerName() + "' not found");
       System.out.println("BOT connected to " + conf.getServerName());

       botUser = new ChatUserImpl(conf.getNick(), this);
       srv.connectUser(botUser);

       IChatChannel[] channels = null;
       channels = srv.listChannels();

       if (channels == null || channels.length == 0) 
            throw new Exception ("Server has no channels");

       
       System.out.println("Channels list: ");
       for (IChatChannel channel : channels){
           System.out.println("\t- " + channel.getName());
       }
       
       System.out.println("Channel in conf: " + conf.getChannelName());

        IChatChannel ch = srv.getChannel(conf.getChannelName());
        if (ch == null) { throw new Exception ("Channel not found");}
        
        IChatUser[] users;
        users = ch.join(botUser);

        if (users == null || users.length == 0) 
            throw new Exception ("No users. This shouldn't happen once we join.");
        
        System.out.println("Users in this channel: ");
        for (IChatUser user : users) {
            System.out.println("\t- " + user.getNick());
        }

        String botWelcomeMsg = "Welcome to channel " + ch.getName();
        ChatMessageImpl msg = new ChatMessageImpl(botUser, ch, botWelcomeMsg);
        ch.sendMessage(msg);

        
        String botPrivateMsg = "Hi, I'm a Bot";
        ChatMessageImpl privateMsg = new ChatMessageImpl(botUser, users[1], botPrivateMsg);
        ch.sendMessage(privateMsg);
        
        
   }

   public static void main (String args [])  {
       ChatRobot cr = new ChatRobot (ChatConfiguration.parse (args));
       try {
        cr.work ();
       } catch (Exception e) {
           System.err.println("Something went wrong: " + e.getMessage());
       }
   }
}
