# Conditionals Directives
libs_for_gcc = -lgnu
normal_libs =

foo: $(objects)
ifeq ($(CC),gcc)
	$(CC) -o foo $(objects) $(libs_for_gcc)
else
	$(CC) -o foo $(objects) $(normal_libs)
endif

#  Include Directive
# suspend reading the current makefile and read one or more other makefiles before continuing
include a.mk b.mk c.mk

# The override Directive
# set the variable in the makefile even though it was set with a command argument
override variable = value
override variable := value
