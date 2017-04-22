sudo apt-get update
sudo apt-get install libtbb-dev
sudo apt-get remove --auto-remove libtbb-dev
sudo apt-get purge --auto-remove libtbb-dev

sudo apt-get install tbb-examples
sudo apt-get remove --auto-remove tbb-examples
sudo apt-get purge --auto-remove tbb-examples

g++ test.cpp -ltbb

# /usr/include/tbb
# /usr/share/doc/libtbb-doc
# /usr/share/doc/tbb-examples
# /usr/share/doc/tbb-examples/examples/parallel_for/tachyon/android/src/com/intel/tbb
# /usr/share/doc/tbb-examples/examples/common/gui/xcode/tbbExample
# /usr/share/doc/libtbb2
# /usr/share/doc/libtbb-dev
