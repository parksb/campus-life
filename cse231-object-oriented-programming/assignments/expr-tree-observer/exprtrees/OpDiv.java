package exprtrees;


public class OpDiv extends BinOp {

	public OpDiv(Expr l, Expr r) {
		setLeft(l); setRight(r);
	}

	public String getOperator() { return "/"; }

	@Override
	public double eval() {
		return getLeft().eval()/getRight().eval();
	}

}
