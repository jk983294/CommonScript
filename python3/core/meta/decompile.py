import dis
import opcode


def countdown(n):
    while n > 0:
        print('T-minus', n)
        n -= 1
    print('Blastoff!')


def generate_opcodes(codebytes):
    extended_arg = 0
    i = 0
    n = len(codebytes)
    while i < n:
        op = codebytes[i]
        i += 1
        if op >= opcode.HAVE_ARGUMENT:
            oparg = codebytes[i] + codebytes[i+1]*256 + extended_arg
            extended_arg = 0
            i += 2
            if op == opcode.EXTENDED_ARG:
                extended_arg = oparg * 65536
                continue
        else:
            oparg = None
        yield (op, oparg)


dis.dis(countdown)
c = countdown.__code__.co_code          # bytecode
print(c)
print(opcode.opname[c[0]])              # SETUP_LOOP

for op, oparg in generate_opcodes(c):
    print(op, opcode.opname[op], oparg)


