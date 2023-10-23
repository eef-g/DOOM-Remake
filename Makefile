all: compile link run

compile: 
	g++ -Isrc/include -c bin/*.cpp 

link:
	g++ *.o -o bin/build/main.exe -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	bin/build/main.exe