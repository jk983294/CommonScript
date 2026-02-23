pip install conan
conan profile detect --force

mkdir -p build && cd build
# 根据 conanfile.txt下载 Boost 头文件并生成 CMake 所需的配置文件
conan install .. --output-folder=.  --build=missing -s build_type=Release
conan install .. --output-folder=.  --build=missing -s build_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

# find package
conan cache path boost/1.90.0
ls /home/aaron/.conan2/p/boost86ef7f340dadb/p/include/boost/
find /home/aaron/.conan2/p/boost86ef7f340dadb/p/include/boost/ -name "unordered_flat_map.hpp" -type f

# gcc system default include paths
echo | gcc -E -v