public abstract class BinOp extends Expr implements Term {

    private Expr mLeft;
    private Expr mRight;

    @Override
    public void printInfix() {
        System.out.print("(");
        mLeft.printInfix();
        System.out.print(getOperator());
        mRight.printInfix();
        System.out.print(")");
    }

    public Expr getLeft() {
        return mLeft;
    }

    public Expr getRight() {
        return mRight;
    }

    public void setLeft(Expr l) {
        mLeft = l;
    }

    public void setRight(Expr r) {
        mRight = r;
    }

    @Override
    public void setVar(String x, double val) {
        if (!(mLeft instanceof NumReal)) {
            ((Term) mLeft).setVar(x, val);
        }

        if (!(mRight instanceof NumReal)) {
            ((Term) mRight).setVar(x, val);
        }
    }

    public abstract String getOperator();

}
