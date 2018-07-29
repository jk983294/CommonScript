#!/bin/bash

npm install gitbook-cli -g

# install plugin
gitbook install ./

gitbook init
gitbook serve

gitbook build
cd _book/
chrome index.html

gitbook pdf ./ ./mybook.pdf
gitbook epub ./ ./mybook.epub
gitbook mobi ./ ./mybook.mobi
