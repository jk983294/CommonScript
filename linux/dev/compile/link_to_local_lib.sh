# link to local .h and lib, the idea is to put -I and -L(-Wl,-rpath) as first as you can
# for lib, you need both -L(for compile time lookup) and -Wl,-rpath(for runtime lookup)
PROJ_INC = -I/home/kun/git/aaa/include/ $(OTHER_INC)
PROJ_LIB_PATH = -Wl,-rpath=/home/kun/git/aaa/lib -L/home/kun/git/aaa/lib $(OTHER_LIB_PATH)
