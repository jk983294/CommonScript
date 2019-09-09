#!/bin/bash

python3 -m venv tutorial-env
source tutorial-env/bin/activate

pip install requests==2.6.0
pip install --upgrade requests
pip show requests
pip list