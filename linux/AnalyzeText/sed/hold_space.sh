#!/bin/bash

# reverse two lines
sed -n '/first line/{h;n;p;g;p}' afile

# reverse whole file
sed -n '{1!G;h;$p}' afile
