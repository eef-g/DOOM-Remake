all: compile link run

compile: 
	cmake -S . -B build 
link:
	cmake --build build

run:
	build/bin/Debug/TheIsle.exe
