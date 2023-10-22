main: src\main.cpp src\bin\game.cpp
	g++ -std=c++17 src\main.cpp src\bin\game.cpp -Isrc\include\SDL2\include -Lsrc\include\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o build\main.exe
	build\game.exe


.PHONY: clean

clean:
	rm main.exe
