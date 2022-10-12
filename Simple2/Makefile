SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDLLIBS=-lSDL2
# This path would need to change for every developer
#WINLOC=C:/Users/kayle/Desktop/Build
# Environment Variable GAMELOC is set in the development environment
WINLOC=$(GAMELOC)
WINSDLCFLAGS=-I$(WINLOC)/msys2/mingw64/include/SDL2/ -Dmain=SDL_main
WINSDLLIBS=-L$(WINLOC)/msys2/mingw64/lib/ -lmingw32 -mwindows -lSDL2main -lSDL2

Simple.exe: Simple.cpp
	g++ -std=c++17 Simple.cpp -ID:/msys64/mingw64/include/SDL2 -LD:/msys64/mingw64/lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -o Simple

Simple: Simple.cpp
	g++ -g -Wall $(SDLCFLAGS) -o $@ $? $(SDLLIBS)

clean: 
	rm Simple.exe Simple
