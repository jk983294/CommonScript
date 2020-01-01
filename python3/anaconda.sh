#!/bin/bash

bash Anaconda-latest-Linux-x86_64.sh
# change /root/anaconda3 to /opt/anaconda3

# uninstall
rm -rf /opt/anaconda3
rm -rf ~/.condarc ~/.conda ~/.continuum

conda search PACKAGENAME                    # check if installed this package
conda list                                  # list all installed packages
conda list | grep numpy
conda install PACKAGENAME
conda update PACKAGENAME

# create an environment
conda create --name myenv
conda create -n myenv python=3.4            # create an environment with a specific version of Python
conda install python=3.5                    # change base env's python version
conda activate myenv                        # switch between environment
conda activate                              # switch to default env (base)
conda install -n myenv scipy=0.15.0         # install a specific version of a package in given an environment
conda info --envs                           # check current venv, active environment marked with *
python --version                            # check current python version of current environment

# install package
conda install -n myenv pip
source activate myenv
pip <pip_subcommand>

# upgrade to latest python
conda update python

# conda mixed with pip, you should first try conda install over pip intall
conda install pip
pip install --upgrade setuptools

# change source
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --set show_channel_urls yes
