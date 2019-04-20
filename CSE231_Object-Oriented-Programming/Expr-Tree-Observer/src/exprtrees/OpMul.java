package exprtrees;


public class OpMul extends BinOp {

	public OpMul(Expr l, Expr r) {
		setLeft(l); setRight(r);
	}

	public String getOperator() { return "*"; }

	@Override
	public double eval() {
		return getLeft().eval()*getRight().eval();
	}

}
