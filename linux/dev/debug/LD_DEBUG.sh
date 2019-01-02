#!/bin/bash

# output to sym.log
$ LD_DEBUG_OUTPUT=sym.log LD_DEBUG=bindings /bin/ls
$ grep malloc sym.log.15730

$ LD_DEBUG=help ls
Valid options for the LD_DEBUG environment variable are:

  libs        display library search paths
  reloc       display relocation processing
  files       display progress for input file
  symbols     display symbol table processing
  bindings    display information about symbol binding
  versions    display version dependencies
  scopes      display scope information
  all         all previous options combined
  statistics  display relocation statistics
  unused      determined unused DSOs
  help        display this help message and exit

$ LD_DEBUG=bindings prog
$ LD_DEBUG=libs prog
