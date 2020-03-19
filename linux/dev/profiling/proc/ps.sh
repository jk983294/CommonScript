ps aux --sort column        # sort by (pmem|pcpu|rss) (physical memory ratio/CPU ratio/resident set size)
ps axo pid,%cpu,rss,vsz,args,wchan  # like top
ps axfo pid,args                    # show process tree

pstree                              # show process tree
pstree -p pid
pstree -pa pid                      # show argument as well