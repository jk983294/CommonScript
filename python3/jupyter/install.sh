# install anaconda
conda update jupyter                    # update

# launch
jupyter notebook
jupyter notebook --help
jupyter notebook notebook.ipynb             # open the given notebook
jupyter notebook --port 9999                # open with given port
jupyter notebook --no-browser               # open without web browser
jupyter notebook --config=/path/to/myconfig.py      # open with given config

# open new notebook
New Notebook button

# separates data files (nbextensions, kernelspecs) from runtime files (logs, pid files, connection files) 
# from configuration (config files, custom.js)
jupyter --data-dir                          # ~/.local/share/jupyter
jupyter --runtime-dir                       # ~/.local/share/jupyter/runtime
jupyter --paths                             # all Jupyter directories and search paths
jupyter --paths --json                      # output to json format

# Configuration files
jupyter --config-dir                        # show config dir
ls ~/.jupyter
jupyter notebook --generate-config          # create a default config file
vim ~/.jupyter/jupyter_notebook_config.py

# Terminal IPython, prompt the user for some code, and when they’ve entered it, execute it in the same process
ipython