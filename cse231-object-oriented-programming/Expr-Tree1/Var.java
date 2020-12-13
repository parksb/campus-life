public class Var extends Expr implements Term {

    private String mSym;
    private double mVal;
    private boolean flag = false;

    public Var(String s) {
        mSym = s;
    }

    @Override
    public void setVar(String x, double val) {
        if (mSym.equals(x)) {
            mVal = val;
            flag = true;
        }
    }

    @Override
    public void printInfix() {
        if (!flag) {
            System.out.print(mSym);
        } else {
            System.out.print(mVal);
        }
    }

    @Override
    public double eval() {
        return mVal;
    }
}
