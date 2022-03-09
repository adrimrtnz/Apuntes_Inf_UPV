// CSD Mar 2013 Juansa Sendra

public class LimitedPhilo extends Philo {
    public LimitedPhilo(int id, int cycles, int delay, Table table) {super(id, cycles, delay, table);}

    public void run() {
        try {
            table.begin(id);
            for (int i=0; i<cycles; i++) {
                // inicio comer (en el zurdo esto tiene que ser al revés)
                table.enter(id);
                table.takeR(id); delay(); table.takeL(id);
                table.eat(id); randomDelay();
                table.dropR(id); table.dropL(id);
                table.exit(id);
                // fin comer
                table.ponder(id); randomDelay();
            }
            table.end(id);
        } 
        catch (InterruptedException ex) {}
    }
}