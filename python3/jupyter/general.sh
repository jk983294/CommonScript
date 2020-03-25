# how it work
# The Notebook frontend stores code and output, together with markdown notes, 
# in an editable document called a notebook. When you save it, this is sent from your browser 
# to the notebook server, which saves it on disk as a JSON file with a .ipynb extension

# JupyterHub Narratives explore deployment and scaling of the Jupyter Notebook for a group of users

Shift + Enter                       # execute code cell
Alt + Enter                         # runs the current cell and inserts a new one below
Ctrl + Enter                        # run the current cell and enters command mode
Esc                                 # Command mode, navigate around the notebook using keyboard shortcuts
Enter                               # Edit mode

# Command mode
# Help->Keyboard Shortcuts dialog lists the available shortcuts
Y                                   # change cell to code
M                                   # change cell to markdown
R                                   # change cell to raw
1-6                                 # change cell to heading 1-6
A                                   # insert cell above
B                                   # insert cell below
X                                   # cut selected cells
C                                   # copy selected cells
V                                   # paste cells below
Z                                   # undo cell deletion
D+D                                 # delete selected cells
I+I                                 # interrupt the kernel
0+0                                 # restart the kernel