package utils_jms;

import javax.jms.JMSContext;
import javax.naming.InitialContext;

/**
 * Initial context for our programs.
 * 
 * <p>Either ChatClientJMS or ChatServerJMS both need an initial context,
 * and a default JMSContext.
 * 
 * <p> This small object keeps these initial context data altogether
 * 
 * <p> We always need this data handy, to create new contexts, and to close 
 * its context on disconnection.
 * 
 * @author Pablo Galdamez
 */
public class TheInitialContext {

    private InitialContext ic;
    private JMSContext ctx;
    
    public TheInitialContext (InitialContext ic, JMSContext ctx) {
        
        // Save initial context, since we need it to lookup.
        //
        this.ic = ic;
       
        // Save the default JMS context
        //
        this.ctx = ctx;        
    }

    
    /**
     * Get the initial context
     * 
     * @return the initial context
     */    
    public InitialContext ic() {
        return ic;
    }

    /**
     * Create a new context, having default context as parent.
     * 
     * @return new context.
     */
    public JMSContext newContext () {
        return ctx.createContext (JMSContext.AUTO_ACKNOWLEDGE);        
    }    

    /**
     * Close the inital context.
     * 
     * <p>This should only be used when disconnecting from JMS.
     * 
     * @throws Exception Errors
     */    
    public void close () throws Exception {
        ctx.close();
        ic.close();
    }
    
}
