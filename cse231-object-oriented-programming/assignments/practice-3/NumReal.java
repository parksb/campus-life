package prac;

public class NumReal extends Expr {

    private double mVal;

    public void set (double v) {
        mVal = v;
    }

    public void printInfix() {
        System.out.print(mVal);
    }

}
