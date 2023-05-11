public class ThreadTester{

	public static void main(String args[])
	{
		PrintThread thread1, thread2, thread3, thread4;

		thread1 = new PrintThread("thread1");
		thread2 = new PrintThread("thread2");
		thread3 = new PrintThread("thread3");
		thread4 = new PrintThread("thread4");
		
		System.out.println("\nIniciando threads...");

		thread1.start();
		thread2.start();
		thread3.start();
		thread4.start();
		
       System.out.println("Threads iniciadas");
	}
}

class PrintThread extends Thread
{
	private int sleepTime;

	public PrintThread(String str)
	{
		super(str);
		sleepTime = (int) (Math.random() * 5000);
		System.out.println(getName() + " dormirá " + sleepTime +"ms...");
	}

	public void run()
	{
		try {
			System.out.println(getName() + " indo dormir.");
			Thread.sleep( sleepTime );
		} catch (InterruptedException e){
		         System.out.println(e.toString() );
		}
                System.out.println(getName()+" TERMINOU!");
	}
}

