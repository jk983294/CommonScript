# write file
fo = open("foo.txt", "w")
fo.write("Python is a great language.\n")
fo.write("Yeah its great!!\n")
fo.close()

# write with
with open("hello.txt", "w") as f:
    f.write("Hello World")

# write with
with open("hello.txt", "w") as f:
    f.writelines(["Hello", "World"])
