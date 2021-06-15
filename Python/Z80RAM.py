import time, math

class RAM:
    def __init__(self):
        # This Z80 implementation has 1 kilobyte of memory
        self.memory = [0] * 1024

    def READ(self, address):
        assert 0 <= address and address <= 0x3FF
        return self.memory[address]

    def WRITE(self, address, value):
        assert 0 <= address and address <= 0x3FF
        assert 0 <= value and value <= 0xFF
        self.memory[address] = value
