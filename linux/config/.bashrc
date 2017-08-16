# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# for ubuntu normal user, user id starts with 1000
UUSER=$(grep 1000:1000 /etc/passwd | awk -F":" '{print $1}');

# my lib functions
if [ -f /home/$UUSER/bin/functions.sh ]; then
    . /home/$UUSER/bin/functions.sh
fi

# history related
HISTCONTROL=ignoreboth
shopt -s histappend         # append to the history file, don't overwrite it
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary, update the values of LINES and COLUMNS.
shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

is_root && {
    COLO=31
} || {
    COLO='1;32'
}

export PS1=$'$(tput sc)\Ek${HOSTNAME}:${PWD##*/}/\E$(tput rc)\E['${COLO}$'m${USER}\E[0m@\E['${COLO}$'m${HOSTNAME}\E[0m:${PWD} \n$ '

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# aliases
alias c="clear"
alias rm='rm -i'
alias rmall='rm -rf *'
alias vi='vim'
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias psg='ps -ef | grep -i'
alias lsg='ll | grep -i'
alias asg='alias | grep -i'
alias histg="history | grep -i"
alias gitpull='git pull origin master'
alias gitpush='git push origin master'
alias chrome='google-chrome'
alias cdgit='cd ~/github/'
alias ..='cd ..'
alias ...='cd ../..'
alias tree="ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'"

alias g++="g++ -std=c++11 -pthread"
alias gcc="gcc -std=c++11 -pthread"

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# web related
alias which2net="lsof -P -i -n"
alias activeport='netstat -tulanp'
alias publicipinfo="curl ifconfig.me && curl ifconfig.me/host"            # show your public network ip and host

# funny
alias busy="cat /dev/urandom | hexdump -C | grep \"ca fe\""

# Alias definitions.
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

# user specific aliases and functions
export EDITOR='vim'
C_INCLUDE_PATH="/home/$USER/include"; export C_INCLUDE_PATH;
CPLUS_INCLUDE_PATH="/home/$USER/include"; export CPLUS_INCLUDE_PATH;
LIBRARY_PATH="./"; export LIBRARY_PATH;
LD_LIBRARY_PATH="./"; export LD_LIBRARY_PATH;

# perl lib related, choose 'local::lib'
PATH="/home/$USER/perl5/bin${PATH:+:${PATH}}"; export PATH;
PERL5LIB="/home/$USER/perl5/lib/perl5${PERL5LIB:+:${PERL5LIB}}"; export PERL5LIB;
PERL_LOCAL_LIB_ROOT="/home/$USER/perl5${PERL_LOCAL_LIB_ROOT:+:${PERL_LOCAL_LIB_ROOT}}"; export PERL_LOCAL_LIB_ROOT;
PERL_MB_OPT="--install_base \"/home/$USER/perl5\""; export PERL_MB_OPT;
PERL_MM_OPT="INSTALL_BASE=/home/$USER/perl5"; export PERL_MM_OPT;

# TBB
if [ -f /home/$USER/.tbbvars.sh ]; then
    . /home/$USER/.tbbvars.sh
fi
