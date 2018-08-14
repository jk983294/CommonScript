$(<function> <arguments>)

# call function
comma:= ,
empty:=
space:= $(empty) $(empty)                       # space = ' '
foo:= a b c                                     # foo = 'a b c'
bar:= $(subst $(space),$(comma),$(foo))         # substitute all space to comma in foo
