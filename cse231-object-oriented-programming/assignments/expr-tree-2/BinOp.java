package exptree;

public abstract class BinOp extends Expr {
    private Expr mLeft, mRight;

    public BinOp(Expr l, Expr r) {
        mLeft = l;
        mRight = r;
    }

    public abstract void printSelf();

    public void printInfix() {
        System.out.print("(");
        mLeft.printInfix();
        printSelf();
        mRight.printInfix();
        System.out.print(")");
    }


    public Expr getLeft() {
        return mLeft;
    }

    public Expr getRight() {
        return mRight;
    }

    public boolean setVar(String str, double val) {
        boolean res1 = mLeft.setVar(str, val);
        boolean res2 = mRight.setVar(str, val);
        return (res1 | res2);
    }

}
