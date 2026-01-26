import collections

'''
a = 2
b = 3
print(a+b)
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
        '''Implement name=TOS (aka top of stack).'''
        self.environment[name] = self.stack.pop()

    def LOAD_NAME(self, name):
        '''Pushes name's value onto stack'''
        self.stack.push(self.environment[name])

    def BINARY_ADD(self):
        '''Implements binary add.'''
        TOS1 = self.stack.pop()
        TOS2 = self.stack.pop()
        self.stack.append(TOS1 + TOS2)

    def PRINT_EXPR(self):
        '''TOS is removed + printed'''
        print(self.stacck.pop())

    def ceval(self, code):
        '''Interpreter() main function.'''
        # Start Instructions
        for opname, arg in code['co_code']:
            if opname == 'LOAD_CONST':
                self.LOAD_CONST(code['co_consts'][arg])
            elif opname == 'STORE_NAME':
                self.STORE_NAME(code['co_names'][arg])
            elif opname == 'LOAD_NAME':
                self.LOAD_NAME(code['co_names'][arg])
            elif opname == 'BINARY_ADD':
                self.BINARY_ADD()
            elif opname == 'PRINT_EXPR':
                self.PRINT_EXPR()
        # End Instructions



interpreter = Interpreter()
interpreter.ceval(code)
