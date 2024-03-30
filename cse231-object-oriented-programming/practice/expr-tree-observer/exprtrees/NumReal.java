package exprtrees;


public class NumReal extends Expr {
	private	double	val;
	
	public NumReal(double v) {
		val = v;
	}

	public void set(double v) { val = v; }
	
	public void printInfix() {
		System.out.print(" "+val+" ");
	}

	@Override
	public double eval() {
		return val;
	}

	@Override
	public boolean setVar(String x, double v) {
		return true;
	}
}
