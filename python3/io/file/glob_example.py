import glob
import os

# finds all the path names matching a specified pattern according to the rules used by the Unix shell
print(glob.glob("/tm*/sys*"))

# remove all files under one dir, but leave dir un-touch, shutil.rmtree will remove dir itself
data_files = glob.glob('/tmp/test/*')
for data_file in data_files:
    os.remove(data_file)
