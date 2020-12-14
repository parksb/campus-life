package assn;

public class Worker {
	private int balance;
    private int hourlyWage;
	private int totalWage;
	
	public int getTotalWage() {
		return this.totalWage;
	}

	public int getHourlyWage() {
	    return this.hourlyWage;
    }

    public int getBalance() {
	    return this.balance;
    }

	public void setHourlyWage(int wage) {
	    final int minWage = 5580;

	    if (wage < minWage) {
            System.out.println("Worker's hourly wage should be greater than " + minWage);
        } else {
            this.hourlyWage = wage;
        }
    }

	public void setTotalWage(int hour) {
	    final int defaultHour = 40;
	    final float extraWageRatio = 1.5f;
	    final int holidayHour = 8;

	    if (hour <= defaultHour) {
            this.totalWage *= hour;
        } else {
	        int wage = (defaultHour - hour) * this.hourlyWage;
	        int overtimeWage = (int)((defaultHour - hour) * this.hourlyWage * extraWageRatio);
	        int paidHolidayWage = holidayHour * this.hourlyWage;

	        this.totalWage = wage + overtimeWage + paidHolidayWage;
        }
    }

    public void setBalance(int wage) {
	    this.hourlyWage += wage;
    }
}
