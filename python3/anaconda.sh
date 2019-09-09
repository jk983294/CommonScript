#!/bin/bash

bash Anaconda-latest-Linux-x86_64.sh
# change /root/anaconda3 to /opt/anaconda3

# uninstall
rm -rf /opt/anaconda3
rm -rf ~/.condarc ~/.conda ~/.continuum


conda list
conda list | grep numpy
conda install PACKAGENAME
conda update PACKAGENAME

# create an environment
conda create --name myenv
# create an environment with a specific version of Python
conda create -n myenv python=3.4

# install a specific version of a package in given an environment
conda install -n myenv scipy=0.15.0

# check current venv
conda info --envs

# install package
conda install -n myenv pip
source activate myenv
pip <pip_subcommand>


# change python version
conda install python=3.5.1

# upgrade to latest python
conda update python
