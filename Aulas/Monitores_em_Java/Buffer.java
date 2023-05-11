public class Buffer {
 
    private int conteudo;
    private boolean disponivel;
 
    public synchronized void set(int idProdutor, int valor) {
        while (disponivel == true) {
            try {
                System.out.println("Produtor #" + idProdutor + " esperando...");
                wait();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        conteudo = valor;
        System.out.println("Produtor #" + idProdutor + " colocou " + conteudo);
        disponivel = true;
        notifyAll();
    }
 
    public synchronized int get(int idConsumidor) {
        while (disponivel == false) {
            try {
                System.out.println("Consumidor #" + idConsumidor
                        + " esperado...");
                wait();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        System.out.println("Consumidor #" + idConsumidor + " consumiu: "
                + conteudo);
        disponivel = false;
        notifyAll();
        return conteudo;
    }
    
public static void main(String[] args) {
    Buffer bufferCompartilhado = new Buffer();
    Produtor produtor1 = new Produtor(1, bufferCompartilhado, 5);
    Produtor produtor2 = new Produtor(2, bufferCompartilhado, 5);
    Consumidor consumidor1 = new Consumidor(1, bufferCompartilhado, 2);
    Consumidor consumidor2 = new Consumidor(2, bufferCompartilhado, 8);
 
    produtor1.start();
    consumidor1.start();
    produtor2.start();
    consumidor2.start();
}
}

