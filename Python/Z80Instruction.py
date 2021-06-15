class Intruction(object):
    def __init__(self, name="Unnamed", operation=lambda *args: None, address_mode="IMP", cycles=0, bytes=1):
        self.name = name
        self.operation = operation
        self.address_mode = address_mode
        self.cycles = cycles
        self.bytes = bytes
