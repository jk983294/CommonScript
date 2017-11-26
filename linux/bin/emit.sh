#!/bin/bash

. log.sh

CMDFULLNAME=$0
CMDNAME=${0##*/}
[[ $CMDNAME = *..+([0-9]) ]] && CMDNAME=${CMDNAME%%..+([0-9])}
CMDARGS=${1+"$@"}

# copy myself to /var/tmp directory and exec
function copy_exec {
    _TARGET_DIR=/var/tmp

    # check if we alread there
    [[ $CMDFULLNAME = @($_TARGET_DIR*|*$CMDNAME..$$) ]] && return 0

    cp $CMDFULLNAME $_TARGET_DIR/$CMDNAME..$$
    eval 'exec $_TARGET_DIR/$CMDNAME..$$ $CMDARGS'
}

# redirect stdout and stderr into logfile
function init_logfile {
    typeset LOGDIR USETIME USESEC FORCE
    typeset TMPDIR=/var/tmp
    typeset AGETIME=7
    typeset HEADERS=True
    typeset SUBDIRNAME=$CMDNAME

    while [[ $# > 0 ]]; do
        case $1 in
            -a) AGETIME=$2 ; shift ;;
            -d) TMPDIR=$2 ; shift ;;
            -D) LOGDIR=$2 ; shift ;;
            -F) FORCE=True ;;
            -h) HEADERS=False ;;
            -N) SUBDIRNAME=$2 ; shift ;;
            -t) USETIME=True ; USESEC=False ;;
            -T) USETIME=True ; USESEC=True ;;
            *) log_die "$0: unknown option ($1)\n" ;;
        esac
        shift
    done

    [[ -z $LOGDIR ]] && LOGDIR="$TMPDIR/$SUBDIRNAME"

    if [[ ! -d $LOGDIR ]]; then
        mkdir -p $LOGDIR
    fi

    [[ -w $LOGDIR ]] || log_die "$0: no write perm to $LOGDIR\n"

    if [[ ${USETIME:-False} = True ]]; then
        if [[ ${USESEC:-False} = True ]]; then
            FILEEXT=$(date +%Y%m%d.%H%M%S)
        else
            FILEEXT=$(date +%Y%m%d.%H%M)
        fi
    else
        FILEEXT=$(date +%Y%m%d)
    fi

    eval export MESSLOGFILE=$LOGDIR/output.$FILEEXT
    exec 1>> $MESSLOGFILE
    exec 2>&1

    eval export _LOGFILESLIVE=True
    eval export _LOGFILESOWNER=$$

    if [[ $HEADERS = True ]]; then
        echo "Messages from $CMDNAME at $HOSTNAME on $(date)" >> $MESSLOGFILE
    fi
}

function Authorized
{
    #
    # Check for restriction on the number of maximum concurrent processes
    #
    export MAXPROCESS=${MAXPROCESS:-5}
    "${EMITTOOLDIR}"/emit -a increment -m "$MAXPROCESS" -p "$$" "$EMITLOCKFILE" "$EMITPIDFILE"
    case $? in
        0) ;;
        6) return 6 ;;  # this means we exceeded MAXPROCESS
        *) return 1 ;;
    esac

    #
    # Check for maximum number of retries, and initialize spawn counter
    #
    export MAXSPAWN=${MAXSPAWN:-1}
    SPAWNCOUNT=$MAXSPAWN

    #
    # Okay, at this point we have permission to execute $PROGRAM so
    # redirect stdout and stderr to logfiles...
    # Note that we need to make the log directory world writable
    # in case the NEXT user on this system is different.
    #
    if [[  ! -d "$EMITLOGDIR/$EMITLOGNAME" ]];  then
        mkdir -p "$EMITLOGDIR/$EMITLOGNAME"
    fi

    chmod 777 "$EMITLOGDIR/$EMITLOGNAME"

    init_logfile -T -D "$EMITLOGDIR/$EMITLOGNAME"

    # Make sure the lock file and pids file are in sync.
    "${EMITTOOLDIR}"/emit -a audit "$EMITLOCKFILE" "$EMITPIDFILE"

    LogEnvironment

    return 0
} # function Authorized

function BounceChild
{
    case $1 in
        USR2) log_info "$1 Signal Received -- ReInit Environment for $PROGRAM.\n"
            SetEnvironment $PROGRAM_ARGS
            LogEnvironment
            ;;
        *) ;;
    esac

    BOUNCE_CHILD=True
    HaltChild
}

function CheckProgram
{
    FULLNAME=$( set +x ; which $RELNAME 2>/dev/null )
    if [[ -z $FULLNAME ]]; then
        log_error "$RELNAME not found.\n"
        exit 1
    fi

    BASEPATH=$FULLNAME
    while [[ ! -z $BASEPATH ]]; do
        BASEPATH=${BASEPATH%/*}
        if [[ -d $BASEPATH/etc/emit ]]; then
            break
        fi
    done

    PROGRAM=$( basename $RELNAME )

    # PROGRAM_UNDERLIER is used in CheckCore to handle symbolic link filenames...
    PROGRAM_UNDERLIER=$( basename $( /bin/readlink $FULLNAME ) )
} # function CheckProgram

#
# SetEnvironment
#
function SetEnvironment
{
    #
    # Look for custom config files, and source them if found.
    #
    if [[ -f $BASEPATH/etc/emit/default ]]; then
        log_info "Sourcing default environment file: $BASEPATH/etc/emit/default\n"
        . $BASEPATH/etc/emit/default
        log_info "Completed sourcing default environment file: $BASEPATH/etc/emit/default\n"
    fi
    if [[ -f $BASEPATH/etc/emit/$PROGRAM ]]; then
        log_info "Sourcing application environment file: $BASEPATH/etc/emit/$PROGRAM\n"
        . $BASEPATH/etc/emit/$PROGRAM
        log_info "Completed sourcing application environment file: $BASEPATH/etc/emit/$PROGRAM\n"
    fi

    #
    # Set the default log directory
    #
    [[ ${EMITLOGDIR:-UNSET} = UNSET ]] && EMITLOGDIR=/var/tmp

    #
    # Set the default restart interval (seconds)
    #
    [[ ${EMITDELAY:-UNSET} = UNSET ]] && EMITDELAY=10

    # Set the lock file and pids file
    if [[ ${EMITINSTANCE:-UNSET} = UNSET ]]
    then
        EMITLOCKFILE="/var/tmp/emit.${PROGRAM}.lock"
        EMITPIDFILE="/var/tmp/emit.${PROGRAM}.pids"
        EMITLOGNAME="$PROGRAM"
    else
        EMITLOCKFILE="/var/tmp/emit.${PROGRAM}.${EMITINSTANCE}.lock"
        EMITPIDFILE="/var/tmp/emit.${PROGRAM}.${EMITINSTANCE}.pids"
        EMITLOGNAME="${PROGRAM}"
    fi
    EMITFLOCKFILE=${EMITLOCKFILE}
    [[ ${EMITTOOLDIR:-UNSET} = UNSET ]] && EMITTOOLDIR=/home/kun/bin
} # function SetEnvironment

# Write the environment to the log file
function LogEnvironment
{
    for v in PROGRAM FULLNAME PROGRAM_ARGS EMITINSTANCE MAXPROCESS MAXSPAWN EMITDELAY EMITEXITZERO EMITLOGDIR EMITTOOLDIR
    do
        eval echo $v=$`echo $v`
    done
}

#
# SignalHandler -- basically we do one of three things.  Bounce the program,
# bounce the program administratively, and ignore.  The difference
# between the first two is that HUP|INT|TERM will come from the system
# whereas USR[12] will come from a human being
#
function SignalHandler
{
    _SIGNAL_CAUGHT=$1

    case $1 in
        #
        # These SIG's will blow away (or try to) the child process quietly
        # Normally, we expect these from the system (logout, cancel, shutdown)
        #
        HUP|INT|QUIT|TERM)
        log_info "$1 Signal Received -- Terminating $PROGRAM.\n"
        EmitClean 0 ;;
        #
        # These should be used to adminitratively bounce processes.
        #
        USR1|USR2)
        log_info "$1 Signal Received -- Administratively Bouncing $PROGRAM.\n"
        BounceChild $1 ;;
        #
        # Ignore everything else, but at least acknowldge that we got it.
        # Currently, this should probably be an error, since if we are ignoring
        # the bitch, then we should make it here....
        #
        *) log_info "$1 Signal Received -- Ignored.\n" ;;
    esac

}

#
# LogNotAuthorized(returncode)
#
function LogNotAuthorized
{
    case $1 in
        6)    log_error "Maximum number of $PROGRAM processes running\n" ;;
        12)   log_error "$PROGRAM not found\n" ;;
        *)    log_error "$PROGRAM exited with an unrecognized status ($1)\n" ;;
    esac

    return $1

} # function LogNotAuthorized

#
# EmitClean(returncode)
#
function EmitClean
{
    # set MAXSPAWN to 0.  if the program hangs and is unkillable for
    # some reason, HaltChild will eventually fail, which sends us
    # right back to wait for the process.  When it wakes up it will
    # die, because of the signal's it has received and we want to
    # ensure that we don't respawn it.
    MAXSPAWN=0
    SPAWNCOUNT=0
    HaltChild || return $1

    DecrementLock

    log_info "Processing for $PROGRAM is complete\n"

    exit $1

} # function EmitClean

#
# DecrementLock()
#
function DecrementLock
{
    #
    # perform lockfile maintenance only if Authorized() succeeded
    #
    if [[ ${EMITAUTHORIZED:-UNSET} = UNSET ]]; then
        return 0
    fi

    ${EMITTOOLDIR}/emit decrement -p $$ $EMITLOCKFILE $EMITPIDFILE
    return 0
} # function DecrementLock

#
# HaltChild
#
# This is obscene.  Since bash doesn't let us deal with wait as elegantly
# as perl or C.  We assume that the process is dead when we can no
# longer successfully send signals using kill.  If the process
# is hung, say in a disk wait, then we can send signals all day, and
# kill will never fail.
#
function HaltChild
{
    [[ -z $CHILD_PID ]] && return 0

    #
    # This first kill should work -- we should be able to send
    # the signal successfully.  Try again 2 seconds later anyway.
    #
    log_info "Sending SIGTERM to $PROGRAM[$CHILD_PID]\n"
    kill -TERM $CHILD_PID > /dev/null 2>&1

    #
    # Now, if it died, then this will fail, since the PID
    # should be invalid.
    #
    sleep 2
    kill -TERM $CHILD_PID > /dev/null 2>&1 || return 0

    #
    # OK, try TERM again, but don't complain if it fails
    # It is quite possible PROGRAM took longer than 2 seconds to die.
    #
    sleep 5
    log_info "Sending 2nd SIGTERM to $PROGRAM[$CHILD_PID]\n"
    kill $CHILD_PID > /dev/null 2>&1 || return 0
    sleep 2
    kill $CHILD_PID > /dev/null 2>&1 || return 0

    #
    # If this was started from a nohup, then the process is probably
    # ignoring SIGTERM, so try SIGINT
    #
    sleep 5
    log_info "Sending SIGINT to $PROGRAM[$CHILD_PID]\n"
    kill -INT $CHILD_PID > /dev/null 2>&1 || return 0
    sleep 2
    kill -INT $CHILD_PID > /dev/null 2>&1 || return 0


    #
    # If all the above kill's succeed, it implies that the damn
    # PROGRAM just won't die.  Be a bit more forceful.
    #
    sleep 5
    log_info "Sending SIGKILL to $PROGRAM[$CHILD_PID]\n"
    kill -KILL $CHILD_PID > /dev/null 2>&1 || return 0
    sleep 2
    kill -KILL $CHILD_PID > /dev/null 2>&1 || return 0

    #
    # Well, we have a problem -- child just won't die.
    # Act accordingly.
    #
    log_error "Unable to halt $PROGRAM [$CHILD_PID].\n"
    return 1

} # function HaltChild

#
# StatToSig
#
# Maps a standard system return code into the signal which generated it if possible.
#
function StatToSig
{
    typeset SIGS S SIGCOUNT B=128 STATUS=$1

    [[ $STATUS -le $B ]] && return

    # kill -l <status> is supposed to do exactly what we want.
    # Let's see if that works.
    CHILD_SIGNAL=$( kill -l $STATUS 2>/dev/null )
    [[ `echo $CHILD_SIGNAL | wc -w` -eq 1 ]] && return

    (( S = $STATUS - $B ))
    SIGS=$( kill -l )
    CHILD_SIGNAL=$( expr "$SIGS" : ".*[^1-9]$S) \([A-Z0-9]*\)" )
    [[ `echo $CHILD_SIGNAL|wc -w` -eq 1 ]] && return
    unset CHILD_SIGNAL
}

#
# SpawnCheck(returncode)
#
function SpawnCheck
{
    unset CHILD_PID
    if [[ $1 != 0 ]]; then
        if [[ -z $CHILD_SIGNAL ]]; then
            log_error "$PROGRAM Exit Status: $1\n"
        else
            case $CHILD_SIGNAL in
                HUP|INT|KILL|TERM|USR1|USR2)
                    log_info "$PROGRAM Exit Status: $1 (SIG$CHILD_SIGNAL)\n" ;;
                *) log_error "$PROGRAM Exit Status: $1 (SIG$CHILD_SIGNAL)\n"
                    CheckCore ;;
            esac
        fi
    else
        log_info "$PROGRAM Exit Status: $1\n"
    fi
    LogNotice

    #
    # If the application has NOT respawned in more than 12 hours
    # then reset the spawn counter.
    #
    CURRENTTIME=$( CurrentTime )
    (( TIMEDIFF = $CURRENTTIME - $SPAWNTIME ))
    if [[ $TIMEDIFF -gt 43200 ]] ; then
        log_info "Resetting spawn counter (MAXSPAWN = $MAXSPAWN).\n"
        SPAWNCOUNT=$MAXSPAWN
    fi

    [[ $SPAWNCOUNT -gt 0 ]] && (( SPAWNCOUNT = $SPAWNCOUNT - 1 ))
    log_info "Respawn counter for $PROGRAM = $SPAWNCOUNT\n"
    if [[ $SPAWNCOUNT -ne 0 ]]
    then
        log_info "Sleeping for $EMITDELAY seconds\n"
        sleep $EMITDELAY
    fi

    return 0
} # function SpawnCheck

#
# CheckCore()
#
function CheckCore
{
    typeset TOUCH

    #
    # Is there a core file, and NO previous backup yet??
    #
    SAVECORENAME=core.emit.$PROGRAM.$( date +%Y%m%d )
    [[ -f core && ! -f $SAVECORENAME ]] || return 0

    #
    # Is it from $PROGRAM or $PROGRAM_UNDERLIER??
    #
    [[ $( file core 2>&1 ) = *\'@($PROGRAM|$PROGRAM_UNDERLIER)\' ]] || return 0

    TOUCH=/bin/touch

    #
    # OK, this is a bit lazy -- this will fail if the program crashes
    # in the first 5 minutes of each month.  I can live with that....
    #
    # The numerical evaluation of the first date command will drop the
    # leading zero, thus we have to add it back in again.
    #
    (( FIVE_MINUTES_AGO = $( date +%m%d%H%M ) - 5 ))
    if [[ $( date +%m ) -lt 10 ]]; then
        $TOUCH 0$FIVE_MINUTES_AGO .five_minutes_ago
    else
        $TOUCH $FIVE_MINUTES_AGO .five_minutes_ago
    fi
    [[ core -nt .five_minutes_ago ]] || return 0

    #
    # Looks like we have a nice, fresh core dump.  Save it.
    # We only keep ONE of these per day.  You can guess what will happen
    # if a process core dumps $MAXSPAWN number of times.
    #
    mv core $SAVECORENAME
    log_info "Core file for $PROGRAM saved in $SAVECORENAME.\n"

}

#
# CurrentTime()
#
function CurrentTime {
    typeset SECS=0 MONSEC MONTH=$( date +%m )
    LEAPYEAR=$( LeapYear )
    MONTH=${MONTH#0}

    while [[ $MONTH -gt 0 ]] ; do

        case $MONTH in
            1|3|5|7|8|10|12) MONSEC=2678400 ;;
            4|6|9|11) MONSEC=2592000 ;;
            2) [[ $LEAPYEAR -eq 0 ]] && MONSEC=2505600 || MONSEC=2419200 ;;
        esac

        (( SECS = $SECS + $MONSEC ))

        (( MONTH = $MONTH - 1 ))

    done

    (( INTRADAYSECS = (( $( date +%H ) * 60 * 60 )) + (( $( date +%M ) * 60 )) + (( $( date +%S ) )) ))
    (( SECS = $SECS + (( $( date +%d ) * 24 * 60 * 60 )) + $INTRADAYSECS ))

    echo $SECS
}

#
# LeapYear()
#
function LeapYear
{
    typeset YEAR=$( date +%Y)
    if [[ ( ( $(( $YEAR % 4 )) = 0 ) && ( $(( $YEAR % 100 )) != 0 ) ) || ( $(( $YEAR % 400 )) = 0 ) ]]; then
        (( LPYEAR = 0 ))
    else
        (( LPYEAR = 1 ))
    fi

    echo $LPYEAR
}

#
# LogNotice()
#
function LogNotice
{
    log_info "See $MESSLOGFILE for STDOUT and STDERR messages\n"
} # function LogNotice



#
# Main() Logic Section
#

copy_exec                   # copy script into /var/tmp and run

unset EMITAUTHORIZED
RELNAME=$1 ; shift

#
# Save arguments for later use
#
PROGRAM_ARGS=${1+"$@"}

#
# Define the signals we care about
#
SIGNALS="HUP INT QUIT TERM PIPE ALRM WINCH USR1 USR2"

#
# Special signal handler.
#
for SIGNAL in $SIGNALS ; do
    case $SIGNAL in
        HUP|INT|QUIT|TERM|USR1|USR2)
            trap "SignalHandler $SIGNAL" $SIGNAL ;;
        PIPE|ALRM|WINCH)
            trap - $SIGNAL ; trap "" $SIGNAL ;;
        *) ;;
    esac
done

CheckProgram                 # Does it exist??


SetEnvironment $PROGRAM_ARGS        # set environmental variables

if Authorized; then            # main execution loop
    EMITAUTHORIZED=1
    while [[ $SPAWNCOUNT -gt 0 ]]; do
        #
        # We spawn the child process in a subshell which has restored
        # the signal mask to its default state.  If the program plays its
        # own games with signals fine -- we just want to protect it from ours.
        #
        # However, we explicitly ignore USR1 and USR2.
        #
        (
        for SIGNAL in $SIGNALS ; do
            trap - $SIGNAL
            case $SIGNAL in
                USR1|USR2) trap "" $SIGNAL ;;
                *) ;;
            esac
        done
        exec $FULLNAME $PROGRAM_ARGS
        ) &

        CHILD_PID=$!

        SPAWNTIME=$( CurrentTime )

        # get username from $USER if it's set, otherwise get it from whoami.
        if [[ -n "$USER" ]]; then
            EMITUSER="$USER"
        else
            EMITUSER=$(whoami)
        fi

        log_info "Spawned $FULLNAME[$CHILD_PID] from $PWD by $EMITUSER\n"

        while true ; do

            #
            # The next two lines were added to fix a problem with receiving
            # SIGUSR1 while having $EMITEXITZERO set... this would cause the
            # program to exit zero and emit to terminate...
            #

            [[ ! -z $_SIGNAL_CAUGHT ]] && _SIGNAL_CAUGHT_AGED=True
            [[ -z $_SIGNAL_CAUGHT && ! -z $_SIGNAL_CAUGHT_AGED ]] && unset _SIGNAL_CAUGHT_AGED
            unset _SIGNAL_CAUGHT

            wait $CHILD_PID
            CHILD_STATUS=$?

            #
            # Check to see if $EMITEXITZERO is set.  If so, then break out of
            # this loop and let the child exit.  If we were bounced
            #
            if [[ ! -z $EMITEXITZERO && $CHILD_STATUS = 0 && -z $_SIGNAL_CAUGHT && -z $_SIGNAL_CAUGHT_AGED ]]; then
                log_info "Set to stop on zero exit status - exiting.\n"
                LogNotice
                EmitClean $?
                exit 0
            fi

            #
            # If we catch a signal, the above wait returns 0, so we may have
            # wait again.  See SignalHandler.  What we doing here is simulating
            # a real wait command, which would return ERRNO.  Need to do this in
            # perl or C to get that complicated.
            #
            [[ -z $_SIGNAL_CAUGHT ]] && break

        done

        StatToSig $CHILD_STATUS

        #
        # When we get SIGUSR[12], then we skip the SpawnCheck
        #
        if [[ $BOUNCE_CHILD = True ]]; then
            BOUNCE_CHILD=False
        else
            SpawnCheck $CHILD_STATUS
            [[ -z $EMITFORCEENV ]] || SetEnvironment
        fi

    done

else

    LogNotAuthorized $?         # Report authorization failure
    EmitClean $?                 # postprocessing routines

fi

EmitClean $?                     # postprocessing routines
