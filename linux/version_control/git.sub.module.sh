#!/bin/bash

# init
git submodule update --init

# commit submodule to new version
cd submodule_name
git checkout master && git pull
cd ..
git add submodule_name
git commit -m "updating submodule to latest"

# fix branch issue
git submodule deinit -f -- submodule_name
git submodule -b develop add -f http://0.0.0.0:8023/kun/submodule_name.git
cd submodule_name/
git checkout -b develop --track origin/develop
git branch -u origin/develop develop

# remove submodule
# delete section in .gitmodules
# delete section from .git/config
git rm --cached path_to_submodule
rm -rf .git/modules/path_to_submodule
git commit -m 'remove submodule'