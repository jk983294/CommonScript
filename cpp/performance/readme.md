### best practice

| good                              | bad                           |  rational |
| :----:                            | :----:                        | :----: |
| ++i                               |   i++                         | no temp object |
| i += 5                            |   i = i + 5                   | no temp object |
| i1 = i2; i1 += i3; i1 += i4;      |  i1 = i2 + i3 + i4;           | no temp object |
| i << 1                            |   i *= 2   |                  |
| x = y * (1.0 / 1.2)               |   x = y / 1.2                 | * is faster than / |
| v.resize(100); foreach(auto x : data){ v.push_back(x);} |         | allocate before add |
| MyClass(int i_): i(i_){}          |  MyClass(int i_){ i = i_;}    | init list is faster |
| explicit MyClass(int i_): i(i_){} | MyClass(int i_): i(i_){}      | explicit prevent unnecessary conversion  |
|                                   |                               | postpone variable declaration as long as possible |
|       functor                     |     function pointer          | functor can be inlined, function pointer usually not |



GHz即十亿赫兹(10^9 Hz)
