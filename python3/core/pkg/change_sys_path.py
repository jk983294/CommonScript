import sys
sys.path.insert(0, '.')
import pkg3

pkg3.func4.function4()


import pathlib
from os.path import abspath, dirname
cpath = str(pathlib.Path(__file__).resolve().parents[0])            # .
cpath1 = str(pathlib.Path(__file__).resolve().parents[1])           # ..
print(abspath(dirname(__file__)), cpath, cpath1)
sys.path.append(cpath)
sys.path.append(cpath+'/pkg1')
import func1


func1.function1()
