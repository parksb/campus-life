package prac;

public class ExpTreeTest {

    public static void main(String[] args) {
        NumReal	r3 = new NumReal();
        r3.set(3);
        NumReal	r10 = new NumReal();
        r10.set(10);
        NumReal	r100 = new NumReal();
        r100.set(100);
        NumReal	r50 = new NumReal();
        r50.set(50);
        NumReal	r7 = new NumReal();
        r7.set(7);
        OpAdd	add1 = new OpAdd(); add1.set(r3, r10);
        OpSub	sub1 = new OpSub(); sub1.set(r100, r50);
        OpAdd	add2 = new OpAdd(); add2.set(r7,  sub1);
        OpSub	sub2 = new OpSub(); sub2.set(add1, add2);
        System.out.println("Expression 1");
        System.out.println("Infix form");
        sub2.printInfix();
        System.out.println("");

        Var	x = new Var(); x.set("x");
        OpAdd add3 = new OpAdd(); add3.set(x, r10);
        OpSub sub3 = new OpSub(); sub3.set(x, r50);
        OpAdd add4 = new OpAdd(); add4.set(r7, sub3);
        OpSub sub4 = new OpSub(); sub4.set(add3, add4);
        System.out.println("\nExpression 2");
        System.out.println("Infix form");
        sub4.printInfix();

        OpMul	mul1 = new OpMul(); mul1.set(sub2, sub4);
        System.out.println("\nExpression 3");
        System.out.println("Infix form");
        mul1.printInfix();

        OpAdd	add5 = new OpAdd(); add5.set(r100,  x);
        OpDiv	div1 = new OpDiv(); div1.set(mul1,  add5);
        System.out.println("\nExpression 4");
        System.out.println("Infix form");
        div1.printInfix();
        System.out.println("");


    }
}