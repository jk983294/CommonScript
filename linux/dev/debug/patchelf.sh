patchelf --print-rpath pyformula.so

patchelf --set-rpath '/usr/local/lib:/usr/lib/python3.8' pyformula.so