public class ExpTreeTest {

    public static void main(String[] args) {
        NumReal	r3 = new NumReal(3);
        NumReal	r10 = new NumReal(10);
        NumReal	r100 = new NumReal(100);
        NumReal	r50 = new NumReal(50);
        NumReal	r7 = new NumReal(7);
        OpAdd	add1 = new OpAdd(r3, r10);
        OpSub	sub1 = new OpSub(r100, r50);
        OpAdd	add2 = new OpAdd(r7,  sub1);
        OpSub	sub2 = new OpSub(add1, add2);
        System.out.println("Expression 1");
        System.out.print("f(x) = ");
        sub2.printInfix();
        System.out.println("");
        sub2.setVar("x", 3);
        System.out.println("f(3) = "+sub2.eval());
        sub2.setVar("x", 200);
        System.out.println("f(200) = "+sub2.eval());

        Var	x = new Var("x");
        OpAdd add3 = new OpAdd(x, r10);
        OpSub sub3 = new OpSub(x, r50);
        OpAdd add4 = new OpAdd(r7, sub3);
        OpSub sub4 = new OpSub(x, add4);
        System.out.println("\nExpression 2");
        System.out.print("g(x) = ");
        sub4.printInfix();
        System.out.println("");
        sub4.setVar("x", 3);
        System.out.println("g(3) = "+sub4.eval());

        OpMul	mul1 = new OpMul(sub2, sub4);
        System.out.println("\nExpression 3");
        System.out.print("h(x) = ");
        mul1.printInfix();
        System.out.println("");

        OpAdd	add5 = new OpAdd(r100,  x);
        OpDiv	div1 = new OpDiv(x,  add5);
        System.out.println("\nExpression 4");
        System.out.print("q(x) = ");
        div1.printInfix();
        System.out.println("");

        div1.setVar("x", 3);
        System.out.println("q(3) = "+div1.eval());
        div1.setVar("x", -5);
        System.out.println("q(-5) = "+div1.eval());
    }
}