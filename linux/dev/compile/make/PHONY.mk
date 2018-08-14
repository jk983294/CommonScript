# in case there is same name file there to break the target
.PHONY: doc clean distclean install tags installetc  installscript

clean:
  rm -rf *.o
