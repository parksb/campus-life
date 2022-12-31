/**
 * Assignment 2
 * Department of Digital Media 201700000 박성범
 * 2018.3.24
 */

package wagecalculator;

public class AjouCorporation {

    private Employee employee1 = new Employee();
    private Employee employee2 = new Employee();
    private Employee employee3 = new Employee();

    // id = 1, 2, and 3 for employee1, employee2, and employee3, respectively
    public boolean setEmployeeWorktime(int id, int basePay, int hoursWorked) {
        int idMin = 1;
        int idMax = 3;
        int payMin = 5580;

        // if one of the arguments is not valid, return false.
        if (id < idMin) {
            System.out.println("id must be greater than " + idMin + ".");
            return false;
        } else if (id > idMax) {
            System.out.println("id must be less than " + idMax + ".");
            return false;
        }

        if (basePay < 5580) {
            System.out.println("basePay must be greater than " + payMin + ".");
            return false;
        } else {
            switch (id) {
                case 1:
                    employee1.setBasePay(basePay);
                    break;
                case 2:
                    employee2.setBasePay(basePay);
                    break;
                case 3:
                    employee3.setBasePay(basePay);
                    break;
            }
        }

        if (hoursWorked < 0) {
            System.out.println("hoursWorked must be greater than zero.");
            return false;
        } else {
            switch (id) {
                case 1:
                    employee1.setHoursWorked(hoursWorked);
                    break;
                case 2:
                    employee2.setHoursWorked(hoursWorked);
                    break;
                case 3:
                    employee3.setHoursWorked(hoursWorked);
                    break;
            }
        }

        return true;
    }

    public int getWage(int id) {
        int wage = 0;
        int idMin = 1;
        int idMax = 3;

        // if id is not valid, return 0.
        if (id < idMin) {
            System.out.println("id must be greater than " + idMin + ".");
            return 0;
        } else if (id > idMax) {
            System.out.println("id must be less than " + idMax + ".");
            return 0;
        }

        switch (id) {
            case 1:
                wage = employee1.getWage();
                break;
            case 2:
                wage = employee2.getWage();
                break;
            case 3:
                wage = employee3.getWage();
                break;
        }

        return wage;
    }

}
