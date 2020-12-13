package exprtrees;

public abstract class BinOp extends Expr {
    private Expr mLeft, mRight;

    public boolean setLeft(Expr l) {
        mLeft = l;
        return true;
    }

    public boolean setRight(Expr r) {
        mRight = r;
        return true;
    }

    public Expr getLeft() {
        return mLeft;
    }

    public Expr getRight() {
        return mRight;
    }

    public String getOperator() {
        return null;
    }

    public boolean setVar(String x, double v) {
        boolean leftValid = mLeft.setVar(x, v);
        boolean rightValid = mRight.setVar(x, v);

        if (leftValid || rightValid) {
            this.notifyObservers();
        }

        if ((mLeft instanceof Var) && (mRight instanceof Var)) {
            return leftValid || rightValid;
        }

        return leftValid && rightValid;
    }

    public void printInfix() {
        System.out.print("(");
        mLeft.printInfix();
        System.out.print(getOperator());
        mRight.printInfix();
        System.out.print(")");
    }
}
