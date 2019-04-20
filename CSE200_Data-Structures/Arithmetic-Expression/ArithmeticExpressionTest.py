import Stack as stk


valStack = stk.Stack()
opStack = stk.Stack()


def main():
    print(evalExp())


def doOp():
    op = opStack.pop()

    if op != '(' and op != ')':
        oper1 = valStack.pop()
        oper2 = valStack.pop()

        if op == '+':
            valStack.push(oper1 + oper2)
        elif op == '-':
            valStack.push(oper2 - oper1)
        elif op == '*':
            valStack.push(oper1 * oper2)
        elif op == '/':
            valStack.push(oper2 / oper1)

def prec(op):
    if op == '*' or op == '/':
        return 3
    elif op == '+' or op == '-':
        return 2
    elif op == '(' or op == ')':
        return 1
    elif op == '$':
        return 0


def repeatOps(refOp):
    while(valStack.size() > 1 and prec(refOp) <= prec(opStack.top())):
        doOp()


def evalExp():
    expr = input()
    token = expr.split()

    for tok in token:
        if tok.isdigit():
            valStack.push(int(tok))
        else:
            repeatOps(tok)
            opStack.push(tok)

    repeatOps('$')

    return valStack.top()


if __name__ == '__main__':
    main()