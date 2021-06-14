import numpy as np

# Z80 CPU
class Z80:
    def __init__(self, bus):
        # Reference to bus class
        self.bus = bus

        # Registers
        # 16 bit
        self.PC = 0
        self.SP = 0
        self.IX = 0
        self.IY = 0

        # 8 bit general registers
        # Flag Register bits:
        #   0 = Carry               (C)
        #   1 = Add / Subtract      (N)
        #   2 = Parity / Overflow (P/V)
        #   3 = Not Used            (X)
        #   4 = Half Carry          (H)
        #   5 = Not Used            (X)
        #   6 = Zero Flag           (Z)
        #   7 = Sign Flag           (S)
        self.A, self.F = 0, 0 # registers on the same line can be accessed as a 16bit pair
        self.B, self.C = 0, 0
        self.D, self.E = 0, 0
        self.H, self.L = 0, 0

        # 8 bit alternate registers
        self.A2, self.F2 = 0, 0
        self.B2, self.C2 = 0, 0
        self.D2, self.E2 = 0, 0
        self.H2, self.L2 = 0, 0

        # 8 bit Inturrupt and Refresh
        self.I = 0
        self.R = 0

        self.opcodes = {

        }


    """
    Getters and Setters
    """
    def AF(self):
        return self.A << 8 | self.F

    def BC(self):
        return self.B << 8 | self.C

    def DE(self):
        return self.D << 8 | self.E

    def HL(self):
        return self.H << 8 | self.L



    """
    OPCODES:

    """

    """
    Other Functions
    """
    def clock(self):
        """ Ripped straight from the OneLoneCoder 6502 implementation videos """
        if self.cycles == 0:
            self.opcode = self.GetOpcode()
            self.PC += 1

            intruction = self.dictionary[self.opcode]

            # Set number of clock cycles for this instruction
            self.cycles = intruction.cycles

            # Changes address mode
            additional_cycle_1 = intruction.address_mode.Excecute()

            # Excecute opcode
            additional_cycle_2 = intruction.operate.Excecute()

            self.cycles += (additional_cycle_1 & additional_cycle_2)


test = Z80("bus")
test.Test()
