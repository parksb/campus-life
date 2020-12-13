"""
All Adder Simulator
Department of Digital Media 201700000 박성범
2018.3.22
"""

class LogicGate:
    def __init__(self, n):
        self.label = n
        self.output = None

    def getLabel(self):
        return self.label

    def getOutput(self):
        self.output = self.performGateLogic()
        return self.output


class BinaryGate(LogicGate):
    def __init__(self, n):
        super(BinaryGate, self).__init__(n)
        self.pinA = None
        self.pinB = None

    def getPinA(self):
        if self.pinA == None:
            return int(input("Enter Pin A input for gate " + self.getLabel() + "-->"))
        else:
            return self.pinA.getFrom().getOutput()

    def getPinB(self):
        if self.pinB == None:
            return int(input("Enter Pin B input for gate " + self.getLabel() + "-->"))
        else:
            return self.pinB.getFrom().getOutput()

    def setNextPin(self, source):
        if self.pinA == None:
            self.pinA = source
        elif self.pinB == None:
            self.pinB = source
        else:
            print("Cannot Connect: NO EMPTY PINS")


class UnaryGate(LogicGate):
    def __init__(self, n):
        super(UnaryGate, self).__init__(n)
        self.pin = None

    def getPin(self):
        if self.pin == None:
            return int(input("Enter Pin input for gate " + self.getLabel() + "-->"))
        else:
            return self.pin.getFrom().getOutput()

    def setNextPin(self, source):
        if self.pin == None:
            self.pin = source
        else:
            print("Cannot Connect: NO EMPTY PINS")


class PinGate(UnaryGate):
    def __init__(self, n):
        super(PinGate, self).__init__(n)

    def getPin(self):
        if self.pin == None:
            self.setPin(int(input("Enter Pin input for gate " + self.getLabel() + "-->")))
        return self.pin

    def setPin(self, val):
        self.pin = val

    def performGateLogic(self):
        return self.getPin()


class NotGate(UnaryGate):
    def __init__(self, n):
        super(NotGate, self).__init__(n)

    def performGateLogic(self):
        return not self.getPin()


class OrGate(BinaryGate):
    def __init__(self, n):
        super(OrGate, self).__init__(n)

    def performGateLogic(self):
        a = self.getPinA()
        b = self.getPinB()

        if a == 1 or b == 1:
            return 1
        else:
            return 0


class AndGate(BinaryGate):
    def __init__(self, n):
        super(AndGate, self).__init__(n)

    def performGateLogic(self):
        a = self.getPinA()
        b = self.getPinB()

        if a == 1 and b == 1:
            return 1
        else:
            return 0


class XorGate(BinaryGate):
    def __init__(self, n):
        super(XorGate, self).__init__(n)

    def performGateLogic(self):
        a = self.getPinA()
        b = self.getPinB()

        x = a and (not b)
        y = (not a) and b

        if x == 1 or y == 1:
            return 1
        else:
            return 0


class Connector:
    def __init__(self, fgate, tgate):
        self.fromgate = fgate
        self.togate = tgate
        tgate.setNextPin(self)

    def getFrom(self):
        return self.fromgate

    def getTo(self):
        return self.togate


def main():
    # Create AND Gates
    andGate = []
    andGateCount = 2
    for i in range(andGateCount):
        label = "AND" + str(i)
        andGate.append(AndGate(label))

    # Create OR Gates
    label = "OR"
    orGate = OrGate(label)

    # Create XOR Gates
    xorGate = []
    xorGateCount = 2
    for i in range(xorGateCount):
        label = "XOR" + str(i)
        xorGate.append(XorGate(label))

    # Create Pin Gates
    x = PinGate("x")
    y = PinGate("y")
    z = PinGate("z")

    # Connect the gates
    Connector(x, xorGate[0])
    Connector(x, andGate[1])
    Connector(y, xorGate[0])
    Connector(y, andGate[1])
    Connector(z, xorGate[1])
    Connector(z, andGate[0])
    Connector(xorGate[0], andGate[0])
    Connector(xorGate[0], xorGate[1])
    Connector(andGate[1], orGate)
    Connector(andGate[0], orGate)

    print("Output(C, S): ", orGate.getOutput(), xorGate[1].getOutput())

if __name__ == "__main__":
    main()
