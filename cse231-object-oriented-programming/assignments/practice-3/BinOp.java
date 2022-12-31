package prac;

public class BinOp extends Expr {

    protected Expr mLeft;
    protected Expr mRight;

    public void set(Expr l, Expr r) {
        mLeft = l;
        mRight = r;
    }

    public void printInfix() {

    }

}
