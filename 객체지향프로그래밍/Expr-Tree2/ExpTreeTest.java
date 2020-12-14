package exptree;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class ExpTreeTest {

    public static void main(String[] args) {
        Expr x = new Variable("x");
        Expr y = new Variable("y");
        Expr z = new Variable("z");
        Expr dividend = new OpAdd(new OpMul(x, x), new NumReal(10));
        Expr divisor = new OpMul(new OpSub(y, new NumReal(10)), new OpAdd(z, new NumReal(5)));
        Expr exp = new OpDiv(dividend, divisor);
        exp.printInfix();
        System.out.println("");

        exp.setVar("x", 2);
        exp.setVar("y", 25);
        exp.setVar("z", 5);
        try {
            System.out.println("" + exp.eval());
        } catch (OverflowException ex) {
            System.out.print("A overflow exception has been thrown at ");
            ex.printBadValue();
            System.out.println();
        }

        exp.setVar("z", -5);
        try {
            System.out.println("" + exp.eval());
        } catch (OverflowException ex) {
            System.out.print("A overflow exception has been thrown at ");
            ex.printBadValue();
        }

    }
}
