# https://mrjbq7.github.io/ta-lib/install.html

# Download ta-lib-0.4.0-src.tar.gz
untar and cd
./configure --prefix=/usr
make
sudo make install
ls /usr/lib/ | grep ta_lib

# after intall c++ shared lib then
# install python wrapper
pip install TA-Lib