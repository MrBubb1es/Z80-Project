class Bus:
    def __init__(self):
        """
        The Z80 Processor has a total of 40 pins:
        """
        # 16 Bits for 16 address pins
        self.ADDRESS = 0

        # 8 bits for 8 data pins
        self.DATA = 0

        # 6 bits for system control pins
        self.M1 = 0
        self.MREQ = 0
        self.IORQ = 0
        self.RD = 0
        self.WR = 0
        self.RFSH = 0

        # 5 bits for cpu control pins
        self.HALT = 0
        self.WAIT = 0
        self.INT = 0
        self.NMI = 0
        self.RESET = 0

        # 2 bits for cpu bus control pins
        self.BUSRQ = 0
        self.BUSACK = 0

        # 1 pin for clock
        self.CLK = 0

        # And 2 pins for power that we don't need to program


    def READ_ADDRESS(self, bit):
        # Ensure 0 <= bit <= 15
        assert bit >= 0 and bit <= 15
        # Return the value of the address pin being read
        return (self.ADDRESS & (1 << bit)) >> bit

    def WRITE_ADDRESS(self, bit, val):
        assert bit >= 0 and bit <= 15

        # Set the bit that is being writen to to 0, then use the OR opperation to set its new value
        self.ADDRESS = (self.ADDRESS & ((1 << bit) ^ 0xFFFF)) | (val << bit)


    def READ_DATA(self, bit):
        assert bit >= 0 and bit <= 7
        return (self.ADDRESS & (1 << bit)) >> bit

    def WRITE_DATA(self, bit, val):
        assert bit >= 0 and bit <= 7
        self.DATA = (self.DATA & ((1 << bit) ^ 0xFF)) | (val << bit)




    def READ_M1(self):
        return self.M1

    def WRITE_M1(self, val):
        self.M1 = val

    def READ_MREQ(self):
        return self.MREQ

    def WRITE_MREQ(self, val):
        self.MREQ = val

    def READ_IORQ(self):
        return self.IORQ

    def WRITE_IORQ(self, val):
        self.IORQ = val

    def READ_RD(self):
        return self.RD

    def WRITE_RD(self, val):
        self.RD = val

    def READ_WR(self):
        return self.WR

    def WRITE_WR(self, val):
        self.WR = val

    def READ_RFSH(self):
        return self.RFSH

    def WRITE_RFSH(self, val):
        self.RFSH = val




    def READ_HALT(self):
        return self.HALT

    def WRITE_HALT(self, val):
        self.HALT = val

    def READ_WAIT(self):
        return self.WAIT

    def WRITE_WAIT(self, val):
        self.WAIT = val

    def READ_INT(self):
        return self.INT

    def WRITE_INT(self, val):
        self.INT = val

    def READ_NMI(self):
        return self.NMI

    def WRITE_NMI(self, val):
        self.NMI = val

    def READ_RESET(self):
        return self.RESET

    def WRITE_RESET(self, val):
        self.RESET = val




    def READ_BUSRQ(self):
        return self.BUSRQ

    def WRITE_BUSRQ(self, val):
        self.BUSRQ = val

    def READ_BUSACK(self):
        return self.BUSACK

    def WRITE_BUSACK(self, val):
        self.BUSACK = val




    def READ_CLK(self):
        return self.CLK

    def WRITE_CLK(self, val):
        self.CLK = val




"""
TESTING STUFF:
"""
testBus = Bus()
