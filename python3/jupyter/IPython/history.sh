In[num]
Out[num]
_                       # [-1] last object in output history
__                      # [-2] object in output history
___                     # [-3] object in output history
_i                      # [-1] last object in input history
_ii                     # [-2] object in input history
_iii                    # [-3] object in input history

%history                # show history
%history -n 4-6         # current session 4-6 lines
%hist -g display        # grep history

%dhist                  # directory history with cd

Ctrl + r                # open a search prompt.

%pastebin 3             # take line 3
%pastebin 18-20         # take lines 18 to 20 from the current session
%pastebin ~1/1-5        # take lines 1-5 from the previous session
