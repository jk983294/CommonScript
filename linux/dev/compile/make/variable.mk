# reference to a make variable (use a single dollar sign)
# reference to a shell variable (use two dollar signs)
lowercase = $(shell echo $(1) | awk '{print tolower($$1)}')
uppercase = $(shell echo $(1) | awk '{print toupper($$1)}')

LIST = one two three
all:
    for i in $(LIST); do \
        echo $$i; \
    done
