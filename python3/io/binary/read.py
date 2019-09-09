# Read the entire file as a single byte string
with open('somefile.bin', 'rb') as f:
    data = f.read()
    text = data.decode('utf-8')
    print(text)
