package exprtrees;


public class OpAdd extends BinOp {

	public OpAdd(Expr l, Expr r) {
		setLeft(l); setRight(r);
	}

	public String getOperator() { return "+"; }

	@Override
	public double eval() {
		// TODO Auto-generated method stub
		return getLeft().eval()+getRight().eval();
	}

}
