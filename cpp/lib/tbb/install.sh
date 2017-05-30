g++ test.cpp -ltbb

git clone https://github.com/01org/tbb.git
cd tbb
make
vim ~/.bashrc
# add
source /home/$USER/github/tbb/build/linux_intel64_gcc_cc5.4.0_libc2.23_kernel4.8.0_release/tbbvars.sh
