package exptree;

public class Variable extends Expr {
    private String mVar;
    private double mValue;

    public Variable(String sym) {
        mVar = sym;
    }

    public void printSelf() {
        System.out.print(" " + mVar + " ");
    }

    @Override
    public void printInfix() {
        printSelf();
    }

    public boolean setVar(String str, double val) {
        if (mVar.equals(str)) {
            mValue = val;
            return true;
        }
        return false;
    }

    public double eval() throws OverflowException {
        double mValueAbs = Math.abs(mValue);

        if (mValueAbs < mLowerBound || mValueAbs > mUpperBound) {
            throw new OverflowException(this);
        }

        return mValue;
    }
}
