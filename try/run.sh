touch CMakeLists.txt
mkdir tmp

echo "cmake_minimum_required(VERSION 3.20)" >> CMakeLists.txt
echo "project(Database VERSION 1.0 LANGUAGES CXX)" >> CMakeLists.txt
echo "set(CMAKE_CXX_COMPILER \"/usr/bin/g++-13\")" >> CMakeLists.txt
echo "set(CMAKE_CXX_STANDARD 20)" >> CMakeLists.txt
echo "set(CMAKE_CXX_STANDARD_REQUIRED ON)" >> CMakeLists.txt
echo "list(APPEND CMAKE_PREFIX_PATH \"~/Qt/6.6.3/gcc_64/lib/cmake/\")" >> CMakeLists.txt

echo "if (CMAKE_CXX_COMPILER)" >> CMakeLists.txt
echo "  add_compile_options(" >> CMakeLists.txt
echo "    -Wall" >> CMakeLists.txt
echo "    -Wextra" >> CMakeLists.txt
echo "    -Werror" >> CMakeLists.txt    
echo "    -Wpedantic" >> CMakeLists.txt
echo "    -pedantic" >> CMakeLists.txt 
echo "    -pedantic-errors)" >> CMakeLists.txt 
echo "endif()" >> CMakeLists.txt

echo "find_package(Qt6 REQUIRED COMPONENTS Widgets Core)" >> CMakeLists.txt
echo "qt_standard_project_setup()" >> CMakeLists.txt

echo "set(SOURCES" >> CMakeLists.txt
for ARG in $@; do
  echo "  $ARG" >> CMakeLists.txt
done
echo ")" >> CMakeLists.txt

#echo "set(HEADERS" >> CMakeLists.txt
#echo ")" >> CMakeLists.txt
echo "qt_add_executable(${1%.*} \${SOURCES})" >> CMakeLists.txt
echo "target_link_libraries(${1%.*} PRIVATE Qt6::Widgets Qt6::Core)" >> CMakeLists.txt

cmake . -B tmp/
cmake --build tmp/
mv -f tmp/${1%.*} build/

rm CMakeLists.txt
rm -r tmp

./build/${1%.*}
