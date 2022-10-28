# If your entire team has sdl2-config working via make you could 
# eliminate the ifeq's below and then uncomment the two lines below.

#SDLCFLAGS=`sdl2-config --cflags`
#SDLLIBS=`sdl2-config --libs`

ifeq ($(OS),Windows_NT) 
	USER:=$(shell whoami)
	ifeq ($(USER),desktop-r562qc4\kamja)
		SDLCFLAGS=-IC:\msys64\mingw64\include\SDL2 -Dmain=SDL_main
		SDLLIBS=-LC:\msys64\mingw64\lib -lmingw32 -mwindows -lSDL2main -lSDL2  -lSDL2_mixer
		GCC=C:\msys64\mingw64\bin\g++.exe
	endif
#	run whoami in cmd, copy/paste after $(USER),

#	Your flags should look something like below
#	WINLOC=$(GAMELOC)
#	SDLCFLAGS=-I$(WINLOC)/msys2/mingw64/include/SDL2/ -Dmain=SDL_main
#	SDLLIBS=-L$(WINLOC)/msys2/mingw64/lib/ -lmingw32 -mwindows -lSDL2main -lSDL2
else
	UNAME:=$(shell uname)
	GCC=g++
	ifeq ($(findstring OS,$(UNAME)),OS)
		SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
		SDLLIBS=-lSDL2  -lSDL2_mixer
	endif

	ifeq ($(UNAME),Linux)
		SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
		SDLLIBS=-lSDL2 -lSDL2_mixer
	endif
endif

SRCDIR=src
SRCS=$(SRCDIR)/Simple.cpp $(SRCDIR)/Exception.cpp
HEADERS=$(SRCDIR)/Animation.h $(SRCDIR)/MediaManager.h $(SRCDIR)/Player.h \
$(SRCDIR)/Sprite.h $(SRCDIR)/Exception.h  $(SRCDIR)/Particle.h \
$(SRCDIR)/ProtoGame.h  $(SRCDIR)/TextureInfo.h
EXE=$(BUILDDIR)/Simple.exe
SCRIPTS=Simple.sh Simple.bat

MEDIADIR=img
MEDIA=$(MEDIADIR)/hello.bmp  $(MEDIADIR)/P15_0.bmp  $(MEDIADIR)/P15_1.bmp \
$(MEDIADIR)/P15_2.bmp  $(MEDIADIR)/P15_3.bmp  $(MEDIADIR)/P15_4.bmp \
$(MEDIADIR)/P15_5.bmp  $(MEDIADIR)/player.bmp $(MEDIADIR)/crash.wav

BUILDDIR=build
BUILDFILES=Makefile

$(EXE): $(SRCS)
	$(GCC) -g -Wall $(SDLCFLAGS) -o $@ $+ $(SDLLIBS)

Simple.zip: $(SRCS) $(HEADERS) $(MEDIA) $(BUILDFILES) $(SCRIPTS)
	zip Simple.zip $+

Deploy.zip: $(MEDIA) $(EXE) $(SCRIPTS)
	zip Deploy.zip $+

clean: 
	rm $(BUILDDIR)/*

all: $(EXE) Simple.zip Deploy.zip 