package assn;

public class WageTest {
	public static void main(String[] args) {
		final int workerCount = 3;
		Worker[] worker = new Worker[workerCount];

		for (int i = 0; i < workerCount; i++) {
			worker[i] = new Worker();
		}

		worker[0].setHourlyWage(5580);
		worker[1].setHourlyWage(6470);
		worker[2].setHourlyWage(7530);

		worker[0].setTotalWage(40);
		worker[1].setTotalWage(45);
		worker[2].setTotalWage(50);

		for (int i = 0; i < workerCount; i++) {
			System.out.println("Worker[" + i + "] ");
			System.out.println("Wage: ");
		}
	}
}
