#!/bin/bash

# scroll in tmux
Ctrl + a [
Ctrl + a PgUp
q                                                   # quit scroll mode

# copy
Ctrl-a [                                            # enter copy mode, space key to start select, enter key finish selection
Ctrl-a ]                                            # paste

# session, a session has one or more windows linked to it
tmux new -s my_session
Ctrl-a : new -s my_session                          # create session inside session
Ctrl-a s                                            # select a new session for the attached client interactively
tmux attach                                         # attach to first existing session outside any session
tmux a -t session-name                              # attach to session-name session
tmux new -s myshare                                 # create a session named myshare
tmux -S /tmp/shareds attach -t shared               # attach to socket file /tmp/shareds, named shared
tmux ls | grep : | cut -d. -f1 | awk '{print substr($1, 0, length($1)-1)}' | xargs kill         # kill all sessions

# window, a window occupies the entire screen and may be split into rectangular panes
Ctrl-a c                                            # 创建新窗口
Ctrl-a &                                            # 关闭当前窗口
Ctrl-a number                                       # 切换至指定窗口
Ctrl-a p                                            # 切换至上一窗口
Ctrl-a n                                            # 切换至下一窗口
Ctrl-a l                                            # 在前后两个窗口间互相切换
Ctrl-a w                                            # 通过窗口列表切换窗口
Ctrl-a ,                                            # 重命名当前窗口, 这样便于识别
Ctrl-a .                                            # 修改当前窗口编号；相当于窗口重新排序
Ctrl-a f                                            # 在所有窗口中find keyword

# pane
Ctrl-a !                                            # take out current pane to new window
Ctrl-a x                                            # delete current pane
Ctrl-a direction                                    # 移动光标以选择面板
Ctrl-a %                                            # Split the current pane into two, left and right
Ctrl-a "                                            # Split the current pane into two, top and bottom
