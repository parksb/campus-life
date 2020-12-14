public class NumReal extends Expr {

    private double mVal;

    public NumReal(double v) {
        mVal = v;
    }

    @Override
    public void printInfix() {
        System.out.print(mVal);
    }

    @Override
    public double eval() {
        return mVal;
    }
}
