#!/bin/bash

CMDFULLNAME=$0
CMDNAME=${0##*/}
[[ $CMDNAME = *..+([0-9]) ]] && CMDNAME=${CMDNAME%%..+([0-9])}
CMDARGS=${1+"$@"}
HOSTNAME=$(hostname)
