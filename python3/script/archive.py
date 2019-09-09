import shutil

shutil.unpack_archive('Python-3.3.0.tgz')
shutil.make_archive('py33', 'zip', 'Python-3.3.0')
