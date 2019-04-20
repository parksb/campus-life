package exptree;

public abstract class Expr{

	public static double mLowerBound = 1.0e-4;
	public static double mUpperBound = 1.0e5;
	
	public abstract void printInfix();
	
	public abstract double eval() throws OverflowException;

	public abstract boolean setVar(String str, double val);

}
