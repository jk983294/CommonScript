#!/bin/bash

# arg list, batch operation
:args *.py                                  # load current dir's py files
:argdo %s/foo/bar/ge | update               # change 'foo' to 'bar' for all those files
