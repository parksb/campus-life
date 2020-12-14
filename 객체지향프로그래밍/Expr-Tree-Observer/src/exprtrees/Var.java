package exprtrees;

public class Var extends Expr {
    private String mVar;
    private double mValue;

    public Var(String sym) {
        mVar = sym;
    }

    public void printInfix() {
        System.out.print(" " + mVar + " ");
    }

    public double eval() {
        return mValue;
    }

    @Override
    public boolean setVar(String x, double v) {
        if (mVar.equals(x)) {
            mValue = v;
            return true;
        }

        return false;
    }

}
