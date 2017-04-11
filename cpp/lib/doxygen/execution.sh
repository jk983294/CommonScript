# generate config
doxygen -g doxygen.config

# generate docs
doxygen doxygen.config

# go check file
firefox index.html
google-chrome index.html
