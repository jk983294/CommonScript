# machine option for Intel 386 and AMD x86-64 Options
-masm=dialect                   # output assembly instructions using selected dialect, ‘intel’ or ‘att’ (the default)
-malign-double                  # aligns double, long double, and long long variables on a two-word boundary or a one-word boundary, On x86-64, option is enabled by default.
-mrtd                           # use a different function-calling convention, stdcall or cdecl
-mavx2
-mno-avx2                       # enable or disable the use of instructions
-m32
-m64                            # generate code for a 32-bit or 64-bit environment
