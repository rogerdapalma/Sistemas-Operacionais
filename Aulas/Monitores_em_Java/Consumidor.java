public class Consumidor extends Thread {
    private int idConsumidor;
    private Buffer pilha;
    private int totalConsumir;
 
    public Consumidor(int id, Buffer p, int totalConsumir) {
        this.idConsumidor = id;
        this.pilha = p;
        this.totalConsumir = totalConsumir;
    }
 
    public void run() {
        for (int i = 0; i < totalConsumir; i++) {
            pilha.get(idConsumidor);
        }
        System.out.println("Consumidor #" + idConsumidor + " concluido!");
    }
}
