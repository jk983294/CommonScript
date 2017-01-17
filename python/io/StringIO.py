import StringIO

# StringIO — Read and write strings as files
output = StringIO.StringIO()
output.write('First line.\n')
output.write('Second line.\n')
contents = output.getvalue()                                        # 'First line.\nSecond line.\n'
output.close()


input = StringIO.StringIO('1\n53\n42')
input.readline()
input.readline()
input.readline()
output.close()
