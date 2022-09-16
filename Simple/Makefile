SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDLLIBS=-lSDL2

Simple.exe: Simple.cpp
	g++ -g -Wall  $(SDLCFLAGS) -o $@ $? $(SDLLIBS)

clean:
	rm Simple.exe
	rm Simple