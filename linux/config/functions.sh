#!/bin/bash

is_root() {
    [[ "$USER" = "root" ]] && return 0 || return 1
}

getip() {
    # ifconfig | awk '/inet addr:/{print $2}' | sed 's/addr://' | grep -v '127.0.0.1'
    ifconfig | awk '/inet .*:/{print $2}' | sed 's/.*://' | grep -v '127.0.0.1'
}

# show time of nanosecond, usage like: daten 1508942856453804254
daten() {
    nanosecond=$1
    second=$(expr $nanosecond / 1000000000)
    date -d@$second
}

# usage regex <regex> <file>, it is good to support reverse search
# example: '!/id jk/' '/id jk/' '//'
regex(){
    if (( $# != 2 )); then
        echo "usage regex <regex> <file>"
        return 1
    fi
    expression=$1
    file2search=$2
    # must use double quote since expression may contain space
    awk "$expression" $file2search
}

# make directory and then cd into it
mcd() {
    mkdir -p "$1";
    cd "$1";
}

backup() {
    cp "$1" "$1.bak";
}

# extrtact contents based on file suffix
extract() {
    if [ -f $1 ] ; then
        case $1 in
            *.tar.bz2)   tar xjf $1     ;;
            *.tar.gz)    tar xzf $1     ;;
            *.bz2)       bunzip2 $1     ;;
            *.rar)       unrar x $1     ;;
            *.gz)        gunzip $1      ;;
            *.tar)       tar xf $1      ;;
            *.tbz2)      tar xjf $1     ;;
            *.tgz)       tar xzf $1     ;;
            *.zip)       unzip $1       ;;
            *.Z)         uncompress $1  ;;
            *.7z)        7z x $1        ;;
            *)     echo "'$1' cannot be extracted via extract()" ;;
        esac
    else
        echo "'$1' is not a valid file"
    fi
}

# sort file by space usage
sbs() {
    du -b --max-depth 1 | sort -nr | perl -pe 's{([0-9]+)}{sprintf "%.1f%s", $1>=2**30? ($1/2**30, "G"): $1>=2**20? ($1/2**20, "M"): $1>=2**10? ($1/2**10, "K"): ($1, "")}e';
}

lost(){
	awk "NR==FNR{a[\$0]=1;next}!a[\$0]" $1 $2
}

export COLOR_NC='\e[0m' # No Color
export COLOR_WHITE='\e[1;37m'
export COLOR_BLACK='\e[0;30m'
export COLOR_BLUE='\e[0;34m'
export COLOR_LIGHT_BLUE='\e[1;34m'
export COLOR_GREEN='\e[0;32m'
export COLOR_LIGHT_GREEN='\e[1;32m'
export COLOR_CYAN='\e[0;36m'
export COLOR_LIGHT_CYAN='\e[1;36m'
export COLOR_RED='\e[0;31m'
export COLOR_LIGHT_RED='\e[1;31m'
export COLOR_PURPLE='\e[0;35m'
export COLOR_LIGHT_PURPLE='\e[1;35m'
export COLOR_BROWN='\e[0;33m'
export COLOR_YELLOW='\e[1;33m'
export COLOR_GRAY='\e[0;30m'
export COLOR_LIGHT_GRAY='\e[0;37m'
