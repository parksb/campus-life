package exprobservers;

import exprtrees.Expr;

public class ValueMonitor implements Observer {
    private String name;
    private Expr expr;

    public ValueMonitor(String n, Expr e) {
        this.name = n;
        this.expr = e;
        this.expr.attach(this);
    }

    public void update() {
        System.out.print(this.name + ": ");
        System.out.println(this.expr.eval());
    }
}
