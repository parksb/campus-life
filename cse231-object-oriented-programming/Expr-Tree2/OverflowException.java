package exptree;

public class OverflowException extends Exception {
    private Expr badExpr;

    public OverflowException(Expr expr) {
        this.badExpr = expr;
    }

    public void printBadValue() {
        this.badExpr.printInfix();
    }
}
