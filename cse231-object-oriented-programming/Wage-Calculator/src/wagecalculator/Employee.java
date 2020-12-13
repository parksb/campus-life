/**
 * Assignment 2
 * Department of Digital Media 201700000 박성범
 * 2018.3.24
 */

package wagecalculator;

public class Employee {

    private int basePay;
    private int hoursWorked;

    public int getBasePay() {
        return this.basePay;
    }

    public void setBasePay(int basePay) {
        this.basePay = basePay;
    }

    public int getHoursWorked() {
        return this.hoursWorked;
    }

    public void setHoursWorked(int hoursWorked) {
        this.hoursWorked = hoursWorked;
    }

    public int getWage() {
        int wage = 0;
        int defaultHour = 40;

        // calculate wage
        if (this.hoursWorked <= defaultHour) {
            wage = this.basePay * this.hoursWorked;
        } else { // worked over 40 hours
            float extraWageRatio = 1.5f;
            int holidayHour = 8;

            int regularWage = defaultHour * this.basePay;
            int overtimeWage = (int)((this.hoursWorked - defaultHour) * this.basePay * extraWageRatio);
            int paidHolidayWage = holidayHour * this.basePay;

            wage = regularWage + overtimeWage + paidHolidayWage;
        }

        return wage;
    }

}
