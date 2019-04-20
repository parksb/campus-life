package exptree;

public class NumReal extends Expr {
    private double val;

    public NumReal(double v) {
        val = v;
    }

    public void printSelf() {
        System.out.print(" " + val + " ");
    }

    public double eval() throws OverflowException {
        double valAbs = Math.abs(val);

        if (valAbs < mLowerBound || valAbs > mUpperBound) {
            throw new OverflowException(this);
        }

        return val;
    }

    @Override
    public void printInfix() {
        printSelf();
    }

    @Override
    public boolean setVar(String str, double val) {
        return false;
    }
}
