ifeq ($(OS), Windows_NT)
    EXECUTABLE := build/bin/Debug/TheIsle
else
    EXECUTABLE := build/bin/Debug/TheIsle.exe
endif

all: compile link run

compile: 
	cmake -S . -B build
 
link:
	cmake --build build

run:
	$(EXECUTABLE)