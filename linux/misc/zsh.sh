#!/usr/bin/env bash

sudo apt-get install zsh
cat /etc/shells                                                             # list all available shell
chsh -s /usr/bin/zsh                                                        # change my default shell to zsh
grep jk /etc/passwd                                                         # check if jk's default shell change to zsh
chsh -s /bin/bash                                                           # change back my default shell

prompt -l                                                                   # list all available prompt themes
prompt walters                                                              # change prompt theme