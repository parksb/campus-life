public class OpAdd extends BinOp {

    public OpAdd(Expr l, Expr r) {
        setLeft(l);
        setRight(r);
    }

    @Override
    public String getOperator() {
        return "+";
    }

    @Override
    public double eval() {
        return getLeft().eval() + getRight().eval();
    }

}
