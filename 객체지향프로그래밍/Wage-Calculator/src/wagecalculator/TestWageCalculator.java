/**
 * Assignment 2
 * Department of Digital Media 201700000 박성범
 * 2018.3.24
 */

package wagecalculator;

public class TestWageCalculator {

    public static void main(String[] args) {
        AjouCorporation ajou = new AjouCorporation();

        if (ajou.setEmployeeWorktime(1, 6000, 40)) {
            System.out.println("Employee 1: base = " + 6000 + "  working hours = " + 40 + "  salary = " + ajou.getWage(1));
        }

        if (ajou.setEmployeeWorktime(2, 5580, 45)) {
            System.out.println("Employee 2: base = " + 5580 + "  working hours = " + 45 + "  salary = " + ajou.getWage(2));
        }

        if (ajou.setEmployeeWorktime(3, 8000, 30)) {
            System.out.println("Employee 3: base = " + 8000 + "  working hours = " + 30 + "  salary = " + ajou.getWage(3));
        }
    }

}
