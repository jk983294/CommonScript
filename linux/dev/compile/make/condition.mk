foo: $(objects)
ifeq ($(CC),gcc)
    $(CC) -o foo $(objects) $(libs_for_gcc)
else
    $(CC) -o foo $(objects) $(normal_libs)
endif

ifeq ($(TARGET_ARCH), arm)
    LOCAL_SRC_FILES := arm.cpp
else ifeq ($(TARGET_ARCH), x86)
    LOCAL_SRC_FILES := x86.cpp
else ifeq ($(TARGET_ARCH), mips)
    LOCAL_SRC_FILES := mips.cpp
else
    LOCAL_SRC_FILES := else.cpp
endif
