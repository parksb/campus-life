package prac;

public class Var extends Expr {

    private String mSym;

    public void set(String s) {
        mSym = s;
    }

    public void printInfix() {
        System.out.print(mSym);
    }

}
