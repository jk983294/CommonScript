#!/bin/bash

sudo apt install openafs-client

fs help                                                         # get help on commands
fs apropos                                                      # search by help text
fs bypassthreshold                                              # get/set cache bypass file size threshold
fs checkservers                                                 # check local cell's servers
fs checkvolumes                                                 # check volumeID/name mappings
fs cleanacl                                                     # clean up access control list
fs copyacl                                                      # copy access control list
fs discon                                                       # disconnection mode
fs diskfree                                                     # show server disk space usage
fs examine                                                      # display file/volume status
fs exportafs                                                    # enable/disable translators to AFS
fs flush                                                        # flush file from cache
fs flushall                                                     # flush all data from the cache
fs flushmount                                                   # flush mount symlink from cache
fs flushvolume                                                  # flush all data in volume
fs getcacheparms                                                # get cache usage info
fs getcalleraccess                                              # list callers access
fs getcellstatus                                                # get cell status
fs getclientaddrs                                               # get client network interface addresses
fs getcrypt                                                     # get cache manager encryption flag
fs getfid                                                       # get fid for file(s)
fs getserverprefs                                               # get server ranks
fs listacl                                                      # list access control list
fs listaliases                                                  # list configured cell aliases
fs listcells                                                    # list configured cells
fs listquota                                                    # list volume quota
fs lsmount                                                      # list mount point
fs messages                                                     # control Cache Manager messages
fs mkmount                                                      # make mount point
fs newalias                                                     # configure new cell alias
fs newcell                                                      # configure new cell
fs nukenfscreds                                                 # nuke credentials for NFS client
fs precache                                                     # set precache size
fs quota                                                        # show volume quota usage
fs rmmount                                                      # remove mount point
fs rxstatpeer                                                   # Manage per peer RX statistics
fs rxstatproc                                                   # Manage per process RX statistics
fs setacl                                                       # set access control list
fs setcachesize                                                 # set cache size
fs setcbaddr                                                    # configure callback connection address
fs setcell                                                      # set cell status
fs setclientaddrs                                               # set client network interface addresses
fs setcrypt                                                     # set cache manager encryption flag
fs setquota                                                     # set volume quota
fs setserverprefs                                               # set server ranks
fs setvol                                                       # set volume status
fs storebehind                                                  # store to server after file close
fs sysname                                                      # get/set sysname (i.e. @sys) value
fs uuid                                                         # manage the UUID for the cache manager
fs version                                                      # show version
fs whereis                                                      # list file's location
fs whichcell                                                    # list file's cell
fs wscell                                                       # list workstation's cell
