
cd ~/Documents/cpp/Database/build/
if [[ $1 == "-c" ]]; then
  cmake ..
fi

ln -f compile_commands.json ..
cmake --build .
./Database
cd ..
