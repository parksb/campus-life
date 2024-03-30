package exprtrees;


public class OpSub extends BinOp {

	public OpSub(Expr l, Expr r) {
		setLeft(l); setRight(r);
	}

	public String getOperator() { return "-"; }

	@Override
	public double eval() {
		return getLeft().eval()-getRight().eval();
	}

}
