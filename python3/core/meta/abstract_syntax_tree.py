import ast

# Some Python code
code = '''
for i in range(3):
    print(i)
del i
'''

# Parse into an AST
top = ast.parse(code, mode='exec')
exec(compile(top, '<stdin>', 'exec'))
