# $(error <text ...>;)                          quit
# $(warning <text ...>;)                        warn but won't quit

foo:= a b c
$(error kun found an error! $(foo))             # *** kun found an error! a b c.  Stop.
