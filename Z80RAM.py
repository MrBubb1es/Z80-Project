import time, math

def op(v):
    v *= 4
    if v == 12:
        v -= 1

class RAM:
    def __init__(self):
        # This Z80 implementation has 1 kilobyte of memory
        self.memory = [0] * 1024



testRAM = RAM()
