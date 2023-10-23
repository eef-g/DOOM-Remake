main: src\bin\main.cpp src\bin\game.cpp
	g++ -std=c++17 src\bin\main.cpp src\bin\game.cpp -Isrc\include\SDL2\include -Isrc\include\SDL2_Image\include -Lsrc\include\SDL2\lib -Lsrc\include\SDL2_Image\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o build\game.exe
	build\game.exe

.PHONY: clean

clean:
	rm game.exe
