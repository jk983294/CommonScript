#!/bin/bash

# locale is a set of language and cultural rules

echo $LC_COLLATE                        # the rules for comparing strings
echo $LC_CTYPE                          # string category and handling
echo $LC_MONETARY                       # formatting of monetary values
echo $LC_MESSAGES                       # information about the language messages should be printed in
echo $LC_NUMBERIC                       # formatting of nonmonetary numeric values
echo $LC_PAPER                          # settings related to standard paper size
echo $LC_TIME                           # formatting of data and time values
echo $LANG                              # default locale

locale                                  # display current setting
locale -a                               # list available locale
locale -a | grep -i zh                  # list all chinese locale

systemd

timedatectl                             # display infos
timedatectl set-time 2017-03-16         # auto sync RTC and Local time

localectl                               # display infos



# Red hat
cat /etc/locale.conf

# Debian
cat /etc/default/locale
sudo dpkg-reconfigure locales

# putty locale, Window -> Translation -> Remote character set: UTF-8
