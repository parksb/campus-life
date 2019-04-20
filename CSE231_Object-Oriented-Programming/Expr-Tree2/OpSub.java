package exptree;

import java.io.Serializable;

public class OpSub extends BinOp implements Serializable {

    public OpSub(Expr l, Expr r) {
        super(l, r);
    }

    @Override
    public void printSelf() {
        System.out.print(" - ");
    }

    public double eval() throws OverflowException {
        double result = getLeft().eval() - getRight().eval();
        double resultAbs = Math.abs(result);

        if (resultAbs < mLowerBound || resultAbs > mUpperBound) {
            throw new OverflowException(this);
        }

        return result;
    }

}
