#!/bin/bash

# ${parameter:-word}
# If parameter is unset or null, the expansion of word is substituted.
# Otherwise, the value of parameter is substituted.

echo "$VAR1"
VAR1="${VAR1:-default value}"
echo "$VAR1"                    # default value

VAR1="has value"
VAR1="${VAR1:-default value}"
echo "$VAR1"                    # has value
