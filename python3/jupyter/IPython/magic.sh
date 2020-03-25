# % Line magics work much like OS command-line calls
# %%, Cell magics are functions that get as an argument

# Functions that work with code: %save, %macro, %recall
%run script
%run -t script          # timing
%run -d script          # run with Python’s pdb debugger
%run -p script          # run with profiler
%edit script            # open editor
%load myscript.py       # load script
%macro my_macro 44-47   # create a macro with lines 44 - 47 , then you can re-run via my_macro

# profile
%time 2**128
%timeit code

# search
%psearch a*             # objects beginning with an a
%psearch -e builtin a*  # objects NOT in the builtin space starting in a
%psearch a* function    # all functions beginning with an a
%psearch re.e*          # objects beginning with an e in module re
%psearch r*.e*          # objects that start with e in modules starting in r
%psearch r*.* string    # all strings in modules beginning with r
%psearch -l             # list all available object types

# Functions which affect the shell: %colors, %xmode, %automagic
# Other functions such as %%writefile, %load, or %paste

# misc
%env                    # get, set, or list environment variables
%reset                  # Resets the namespace by removing all names defined by the user
%reset object           # remove object
%precision 3            # set float display precision
%pylab                  # load numpy and matplotlib
%tb                     # Print the last traceback.

# help
%magic
%somemagic?             # read its docstring
%lsmagic                # all the available magic functions

# GUI
%gui wx                 # enable wxPython event loop integration
%gui qt4|qt             # enable PyQt4 event loop integration
%gui qt5                # enable PyQt5 event loop integration
%gui gtk                # enable PyGTK event loop integration
%gui gtk3               # enable Gtk3 event loop integration
%gui tk                 # enable Tk event loop integration
%gui osx                # enable Cocoa event loop integration (requires %matplotlib 1.1)
%gui                    # disable all event loop integration
