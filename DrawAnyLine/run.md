cd DrawAnyLine

cmake -S . -B build -G "MinGW Makefiles"

cmake --build build

build/main.exe