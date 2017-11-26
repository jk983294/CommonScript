#!/bin/bash

# It's recommended to use absolute path when sourcing a script
. ../log.sh

echo "1. use default log settings"
echo

log_debug "hello,world\n"
log_info 'hello,world\n'
log_warn 'hello,world\n'
log_error 'hello,world\n'

echo
echo "2. set loglevel to $LOG_INFO"
echo

set_log_level $LOG_INFO
log_debug "hello,world\n"
log_info 'hello,world\n'
log_warn 'hello,world\n'
log_error 'hello,world\n'

echo
echo "3. set log fmt to [<levelname>] [<asctime>] <message>"
echo

set_log_format "[<levelname>] [<asctime>] <message>"
log_info 'hello,world\n'
log_warn 'hello,world\n'

echo
echo "4. set date fmt to %Y/%m/%d %H:%M:%S"
echo

set_date_format "%Y/%m/%d %H:%M:%S"
log_info 'hello,world\n'
log_warn 'hello,world\n'

echo
echo "5. set log color to green blue '' yellow"
echo

set_log_level $LOG_DEBUG
set_log_color green blue '' yellow
log_debug "hello,world\n"
log_info 'hello,world\n'
log_warn 'hello,world\n'
log_error 'hello,world\n'

echo
echo "6. disable color"
echo

disable_log_color
log_debug "hello,world\n"
log_info 'hello,world\n'
log_warn 'hello,world\n'
log_error 'hello,world\n'

echo
echo '7. use colorful print'
echo

red "hello,world\n"
green "hello,world\n"
yellow "hello,world\n"
cyan "hello,world\n"
gray "hello,world\n"
purple "hello,world\n"
blue "hello,world\n"
white "hello,world\n"

echo
echo '8. exit script'
echo
log_die "exit script\n"
