#!/usr/bin/env bash

# more can only page down large file
# space     page down
# q         quit
more /etc/services

# less can page down and up file, even search content
# space / page down     page down
# page up               page up
# 16G                   go to 16th line
# /http                 search for http string
# n                     go to next occurrence of http string
# q                     quit
less /etc/services
ls -l /etc | less

