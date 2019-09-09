"""
wipe out existing content with "wt"
append to existing file with "at"
"""

# write file
fo = open("foo.txt", "wt")
fo.write("Python is a great language.\n")
fo.write("Yeah its great!!\n")
fo.close()

# write with
with open("hello.txt", "wt") as f:
    f.write("Hello World\n")
    f.writelines(["Hello ", "World", "\n"])
    print("Hello World\n", file=f)
