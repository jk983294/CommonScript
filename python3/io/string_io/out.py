from io import StringIO

# StringIO — Read and write strings as files
output = StringIO()
output.write('1')
output.write('2')
print("3", file=output)
print(output.getvalue())                # 123
output.close()
