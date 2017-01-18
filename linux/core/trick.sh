#!/usr/bin/env bash

!ls                                                         # run last ls cmd, which will contain my last ls arguments
!grep                                                       # run last grep cmd, which will contain my last grep arguments

cd !$                                                       # !$ last cmd's argument, say run mkdir dir1, then !$ resolved to dir1 i.e. cd dir1