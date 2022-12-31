package exprtrees;

import exprobservers.Subject;

public abstract class Expr extends Subject {
	public abstract double eval();
	public abstract void printInfix();
	public abstract boolean setVar(String x, double v);
}
