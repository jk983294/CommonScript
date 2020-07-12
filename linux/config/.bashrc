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
alias h="history"
alias rm='rm -i'
alias rmall='rm -rf *'
alias wcl='wc -l'
alias vi='vim'
alias vir='vim -R'
alias shbeauty='ex +"set syn=sh" +"norm gg=G" -cwq'
alias ll='ls -alhF'
alias la='ls -A'
alias l='ls -CF'
alias gnear='grep -A5 -B5'
alias greprw='grep -rw'
alias psg='ps -ef | grep -i'
alias lsg='ll | grep -i'
alias asg='alias | grep -i'
alias histg="history | grep -i"
alias gitpull='git pull origin master'
alias gitpullo='git pull origin'
alias gitpulld='git pull origin develop'
alias gitpush='git push origin master'
alias gitpushd='git push origin develop'
alias gitpusho='git push origin'
alias gitcd='git checkout develop'
alias gitreset='git reset --hard HEAD'
alias gitdiff='git d'
alias gitinit='git submodule update --init'
alias gitd='git d HEAD@{1}'
alias chrome='google-chrome'
alias cdgit='cd ~/github/'
alias cdm='cd ~/github/midas/install'
alias cdvis='cd ~/github/midas/visualization'
alias cdata='cd ~/Data/ctp'
alias cdconf='cd /opt/version/latest/etc'
alias cdz='cd /opt/version/latest/'
alias c777='chmod +777'
alias ..='cd ..'
alias ...='cd ../..'
alias tree="ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'"
alias du='du -h -d 1'

# text process
alias avg='awk "{ sum += \$1; n++; } END { if (n > 0) print ( sum / n); }"'
alias total='awk "{ sum += \$1; } END { print ( sum ); }"'
alias wordcount='awk "{for(i=1; i<= NF; i++) a[\$i]++} END {for(k in a) print a[k], k}"'
alias sortn1='sort -n -k1'                      # sort by first column numerically
alias cut1='cut -f1 -d" "'
alias cut2='cut -f2 -d" "'
alias cut3='cut -f3 -d" "'
alias cut4='cut -f4 -d" "'
alias cut5='cut -f5 -d" "'
alias rm_comma='sed -i "s/,/ /g"'
alias tailf='tail -f'

alias g++="g++ -std=c++11 -pthread"
alias gcc="gcc -std=c++11 -pthread"
alias make="make -j`nproc`"
alias mcm="make clean; make"
alias mc="make clean"
alias mi="make install"
alias mt="make test"
alias lscore="ls -lrt core.* | tail -1"
alias rmcore="rm -f core.*"
alias gdb='gdb -q'
alias boostc="~/github/CommonScript/linux/dev/compile/asio_compile.pl"
alias tbbc="~/github/CommonScript/linux/dev/compile/tbb_compile.pl"

alias a='admin 0:8023'
alias a3='admin 0:8033'
alias dp='delta_play'
alias ff='field_extract_facility.pl'
alias mdc='md_client.pl'
alias sql='mysql -u $USER -p'
alias vimt='vim /opt/version/latest/etc/trade_config.xml'
alias cmd='~/github/protoss/fleet/command/main.py'
alias compress='tar -cjvf' # usage: compress linux.git.tar.bz /home/kun/github/linux
alias perfrecord='perf record -g'
alias perfreport='perf report -g "graph,0.5,caller"'

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# web related
alias which2net="lsof -P -i -n"
alias activeport='netstat -tulanp'
alias publicipinfo="curl ifconfig.me && curl ifconfig.me/host"            # show your public network ip and host
alias oip="curl www.trackip.net/ip?json" # show outside ip, not internal ip

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
set -o vi
C_INCLUDE_PATH="/home/$USER/include"; export C_INCLUDE_PATH;
CPLUS_INCLUDE_PATH="/home/$USER/include"; export CPLUS_INCLUDE_PATH;
LIBRARY_PATH="/home/$USER/lib${LIBRARY_PATH:+:${LIBRARY_PATH}}"; export LIBRARY_PATH;
LD_LIBRARY_PATH="/home/$USER/lib${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}"; export LD_LIBRARY_PATH;

# perl lib related, choose 'local::lib'
if [ -d /home/$USER/perl5/bin ]; then
    PATH="/home/$USER/perl5/bin${PATH:+:${PATH}}"; export PATH;
    PERL5LIB="/home/$USER/perl5/lib/perl5${PERL5LIB:+:${PERL5LIB}}"; export PERL5LIB;
    PERL_LOCAL_LIB_ROOT="/home/$USER/perl5${PERL_LOCAL_LIB_ROOT:+:${PERL_LOCAL_LIB_ROOT}}"; export PERL_LOCAL_LIB_ROOT;
    PERL_MB_OPT="--install_base \"/home/$USER/perl5\""; export PERL_MB_OPT;
    PERL_MM_OPT="INSTALL_BASE=/home/$USER/perl5"; export PERL_MM_OPT;
fi

# more path
if [ -d /home/$USER/github/CommonScript/python/bin ]; then
    PATH="/home/$USER/github/CommonScript/python/bin${PATH:+:${PATH}}"; export PATH;
fi

if [ -d /home/$USER/github/CommonScript/linux/bin ]; then
    PATH="/home/$USER/github/CommonScript/linux/bin${PATH:+:${PATH}}"; export PATH;
fi

if [ -d /home/$USER/github/midas/install ]; then
    PATH="/home/$USER/github/midas/install${PATH:+:${PATH}}"; export PATH;
fi

if [ -d /opt/version/latest/bin ]; then
    PATH="/opt/version/latest/bin${PATH:+:${PATH}}"; export PATH;
fi

# added by Anaconda3 installer
if [ -d /opt/anaconda3 ]; then
    export PATH="/opt/anaconda3/bin:$PATH"
    alias p3='/opt/anaconda3/bin/python'
fi
if [ -d /opt/miniconda3 ]; then
    export PATH="/opt/miniconda3/bin:$PATH"
    alias p3='/opt/miniconda3/bin/python'
fi


# TBB
if [ -f /home/$USER/.tbbvars.sh ]; then
    . /home/$USER/.tbbvars.sh
fi

# python
if [ -f /home/$USER/github/CommonScript/linux/config/.pythonstartup ]; then
    export PYTHONSTARTUP="/home/$USER/github/CommonScript/linux/config/.pythonstartup"
fi

# git stuff
if [ -f ~/github/CommonScript/linux/version_control/.git-completion.bash ]; then
    . ~/github/CommonScript/linux/version_control/.git-completion.bash
fi
if [ -f ~/github/CommonScript/linux/version_control/.git-prompt.sh ]; then
    . ~/github/CommonScript/linux/version_control/.git-prompt.sh
fi
export GIT_PS1_SHOWDIRTYSTATE=1


if [ -d /usr/local/cuda ]; then
    PATH="/usr/local/cuda/bin${PATH:+:${PATH}}"; export PATH;
    LD_LIBRARY_PATH="/usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}"; export LD_LIBRARY_PATH;
fi
