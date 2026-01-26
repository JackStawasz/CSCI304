import collections

'''
a = 2
b = 3
print(a+b)
print(a-b)
'''

code = {
    'co_code': [
        ('LOAD_CONST', 0),
        ('STORE_NAME', 0),
        ('LOAD_CONST', 1),
        ('STORE_NAME', 1),
        ('LOAD_NAME', 0),
        ('LOAD_NAME', 1),
        ('BINARY_ADD', None),
        ('PRINT_EXPR', None),
        ('LOAD_NAME', 0),
        ('LOAD_NAME', 1),
        ('BINARY_SUB', None),
        ('PRINT_EXPR', None)
    ],
    'co_consts': [2, 3],
    'co_names': ['a', 'b'],
}

class Interpreter:
    '''Reference: https://docs.python.org/3/library/dis.html'''

    def __init__(self):
        self.stack = collections.deque()
        self.environment = {}

    def LOAD_CONST(self, const):
        '''Pushes const onto the stack.'''
        self.stack.append(const)

    def STORE_NAME(self, name):
        '''Implements name = TOS.'''
        self.environment[name] = self.stack.pop()

    def LOAD_NAME(self, name):
        '''Pushes the value associated with name onto the stack.'''
        self.stack.append(self.environment[name])

    def BINARY_ADD(self):
        '''Implements the binary add.'''
        TOS = self.stack.pop()
        TOS1 = self.stack.pop()
        self.stack.append(TOS+TOS1)

    def BINARY_SUB(self):
        '''Implements the binary subtraction.'''
        TOS = self.stack.pop() # Right side of '-' pops first
        TOS1 = self.stack.pop() # Left side of '-' pops second
        self.stack.append(TOS1-TOS) # Perform subtraction

    def PRINT_EXPR(self):
        '''TOS is removed from the stack and printed.'''
        print(self.stack.pop())

    def ceval(self, code):
        '''Interpreter main loop.'''
        # Start instructions
        for opname, arg in code['co_code']:
            if opname == 'LOAD_CONST':
                self.LOAD_CONST(code['co_consts'][arg])
            elif opname == 'STORE_NAME':
                self.STORE_NAME(code['co_names'][arg])
            elif opname == 'LOAD_NAME':
                self.LOAD_NAME(code['co_names'][arg])
            elif opname == 'BINARY_ADD':
                self.BINARY_ADD()
            elif opname == 'BINARY_SUB':
                self.BINARY_SUB()
            elif opname == 'PRINT_EXPR':
                self.PRINT_EXPR()
        # End instructions

interpreter = Interpreter()
interpreter.ceval(code)

