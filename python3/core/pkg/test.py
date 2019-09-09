import learn.core.pkg.pkg1 as pk1
import learn.core.pkg.virtual_module as vm
import learn.core.pkg.pkg2 as pk2

pk1.func1.function1()
pk1.func2.function2()
pk1.iwrp.function_relative_test()

a = vm.A()
b = vm.B()

print(pk2.func3.get_data())
