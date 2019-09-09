import glob
import tarfile
import time

data_files = glob.glob('/tmp/*.txt')
tar = tarfile.open('/tmp/backup/%s.tar' % time.strftime("%Y%m%d_%H%M%S", time.localtime()), "w")
for data_file in data_files:
    tar.add(data_file)
tar.close()
