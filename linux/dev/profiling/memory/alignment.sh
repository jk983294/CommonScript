1 memory > many chip > 8 banks
1 bank is a matrix, one cell of matrix is 1 byte
0x0000-0x0007 continous bytes spread in 8 banks, they work in parallel
this hardware structure decide 8 byte alignment

每当CPU向内存请求数据的时候，内存芯片总是8个bank并行一起工作。
每个bank在定位到行地址后，把对应的行copy到row buffer。 再根据列地址把对应的元素中的数据取出来，8个bank把数据拼接一下，一个64位宽的数据就可以返回给CPU了