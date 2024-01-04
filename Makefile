all: compile run

setup: 
	git submodule update --init --recursive --depth 1
	if not exist "build" mkdir build

compile: 
	cd build && cmake .. -G "MinGW Makefiles"
	cd build && make

run: 
	cd build && ./DOOM.exe