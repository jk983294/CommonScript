# if a variable has been set with a command argument, then ordinary assignments in the makefile are ignored
# you need to override command argument
override variable += more_text

# override directives
override define foo =
bar
endef
