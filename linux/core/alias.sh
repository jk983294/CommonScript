#!/bin/bash

alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'
alias                                               # show current aliases
unalias ls                                          # unalias ls alias
type ls                                             # check ls cmd is aliased to something else

\ls                                                 # use un-aliased ls version, raw version
