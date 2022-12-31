package prac;

public class OpDiv extends BinOp {

    public void printInfix() {
        System.out.print("(");
        mLeft.printInfix();
        System.out.print(" / ");
        mRight.printInfix();
        System.out.print(")");
    }

}
