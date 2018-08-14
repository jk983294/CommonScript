# $(call func, arg1, arg2, ...)
reverse = $(2) $(1)
foo = $(call reverse, a, b)                     # foo is "b a"

# define functions which could be used later
# below is reverse wildcard
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
HEADER := $(call rwildcard,$(INCLUDE_PATH),*.h)         # header files

# functions
lowercase = $(shell echo $(1) | awk '{print tolower($$1)}')
uppercase = $(shell echo $(1) | awk '{print toupper($$1)}')
