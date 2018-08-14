INC += -I$(INCLUDE_PATH)                                # include path
MY_LIB_PATH = -L$(INSTALL_PATH)/lib                     # lib path

# warn linker, rpath gives relative path of so files, LD_LIBRARY_PATH requires full path
# rpath designates the run-time search path hard-coded in an executable file or library.
# dynamic linking loaders use the rpath to find required libraries
LIB_PATH=$(PREFIX)/lib
LIBS += -Wl,-rpath=$(LIB_PATH) -L$(LIB_PATH)
