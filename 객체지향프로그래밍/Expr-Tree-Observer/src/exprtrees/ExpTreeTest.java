package exprtrees;

import exprobservers.ValueMonitor;

public class ExpTreeTest {

    public static void main(String[] args) {
        Expr x = new Var("x");
        Expr y = new Var("y");
        Expr x_2 = new OpSub(x, new NumReal(2));
        Expr y_2 = new OpSub(y, new NumReal(2));
        Expr term1 = new OpMul(x_2, x_2);
        Expr term2 = new OpMul(y_2, y_2);
        Expr term3 = new OpMul(new OpMul(x, y), new NumReal(4));
        Expr fxy = new OpSub(new OpAdd(term1, term2), term3);
        ValueMonitor mon1 = new ValueMonitor("monitor1", term1);
        ValueMonitor mon2 = new ValueMonitor("monitor2", term2);
        ValueMonitor mon3 = new ValueMonitor("monitor3", term3);
        ValueMonitor mon4 = new ValueMonitor("monitor4", fxy);
        fxy.setVar("x", 3);
        fxy.setVar("y", 5);
    }
}
