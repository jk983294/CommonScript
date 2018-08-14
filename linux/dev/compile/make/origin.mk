# $(origin <variable>)
# undefined                 never defined
# default                   like CC
# environment               from env, and no -e option when execute Makefile
# file                      from Makefile
# command line
# override
# automatic

ifdef foo
    ifeq "$(origin foo)" "environment"
        foo = bar
    endif
endif
