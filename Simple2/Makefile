# If your entire team has sdl2-config working via make you could 
# eliminate the ifeq's below and then uncomment the two lines below.

#SDLCFLAGS=`sdl2-config --cflags`
#SDLLIBS=`sdl2-config --libs`

ifeq ($(OS),Windows_NT) 
	USER:=$(shell whoami)
	ifeq ($(USER),desktop-r562qc4\kamja)
		SDLCFLAGS=-IC:\msys64\mingw64\include\SDL2 -Dmain=SDL_main
		SDLLIBS=-LC:\msys64\mingw64\lib -lmingw32 -mwindows -lSDL2main -lSDL2  -lSDL2_mixer -lSDL2_ttf
		GCC=C:\msys64\mingw64\bin\g++.exe
	endif
	ifeq ($(USER),desktop-c7fid61\pichuve)
		SDLCFLAGS=-IC:\SDL2\include\SDL2 -Dmain=SDL_main
		SDLLIBS=-LC:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
		GCC=C:\msys64\mingw64\bin\g++.exe
	endif
	ifeq ($(USER),kayle)
	SDLCFLAGS=-ID:/msys64/mingw64/include/SDL2 -Dmain=SDL_main
	SDLLIBS=-LD:/msys64/mingw64/lib -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf
	GCC=g++
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

#Ben's Compile

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin) # MacOS 
#		SDLCFLAGS=-I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
#		SDLLIBS=-L/opt/homebrew/lib -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_main - lSDL2_image
		GCC=clang++ -std=c++11 -stdlib=libc++
		SDLCFLAGS=`sdl2-config --cflags`
		SDLLIBS=`sdl2-config --libs` -lSDL2 -lSDL2_mixer -lSDL2_ttf  
#-lSDL2_Dear_ImGui
endif

SRCDIR=src
SRCS=$(SRCDIR)/Simple.cpp $(SRCDIR)/Exception.cpp $(SRCDIR)/imgui.cpp $(SRCDIR)/imgui_demo.cpp $(SRCDIR)/imgui_draw.cpp $(SRCDIR)/imgui_tables.cpp $(SRCDIR)/imgui_widgets.cpp $(SRCDIR)/imgui_impl_sdl.cpp $(SRCDIR)/imgui_impl_sdlrenderer.cpp $(SRCDIR)/imgui_stdlib.cpp
EXE=$(BUILDDIR)/Simple.exe
SCRIPTS=Simple.sh Simple.bat

MEDIADIR=img
MEDIA=$(MEDIADIR)/earthshine.mp3  $(MEDIADIR)/farmland.bmp  $(MEDIADIR)/ground.bmp  $(MEDIADIR)/sellchest.bmp  $(MEDIADIR)/npc.bmp \
$(MEDIADIR)/HoneyshroomsStage_0.bmp  $(MEDIADIR)/HoneyshroomsStage_1.bmp  $(MEDIADIR)/HoneyshroomsStage_2.bmp \
$(MEDIADIR)/ElaberriesStage_0.bmp  $(MEDIADIR)/ElaberriesStage_1.bmp  $(MEDIADIR)/ElaberriesStage_2.bmp \ $(MEDIADIR)/ElaberriesStage_3.bmp \
$(MEDIADIR)/MoonflowersStage_0.bmp  $(MEDIADIR)/MoonflowersStage_1.bmp  $(MEDIADIR)/MoonflowersStage_2.bmp \
$(MEDIADIR)/morning_0.bmp  $(MEDIADIR)/morning_1.bmp $(MEDIADIR)/morning_2.bmp \
$(MEDIADIR)/morning_3.bmp  $(MEDIADIR)/morning_4.bmp  $(MEDIADIR)/morning_5.bmp \
$(MEDIADIR)/morning_6.bmp  $(MEDIADIR)/morning_7.bmp  $(MEDIADIR)/Pixeled.ttf \
$(MEDIADIR)/plant.wav  $(MEDIADIR)/player_0.bmp  $(MEDIADIR)/player_1.bmp \
$(MEDIADIR)/player_2.bmp  $(MEDIADIR)/player_3.bmp  $(MEDIADIR)/spritesheet.bmp \
$(MEDIADIR)/star.bmp  $(MEDIADIR)/water.wav

BUILDDIR=build
BUILDFILES=Makefile

$(EXE): $(SRCS)
	$(GCC) -g -Wall $(SDLCFLAGS) -o $@ $+ $(SDLLIBS)

run: $(EXE)
	./$(EXE)

Simple.zip: $(SRCS) $(HEADERS) $(MEDIA) $(BUILDFILES) $(SCRIPTS)
	zip Simple.zip $+

Deploy.zip: $(MEDIA) $(EXE) $(SCRIPTS)
	zip Deploy.zip $+

clean: 
	rm $(BUILDDIR)/*

cleanExe:
	rm $(EXE)

all: $(EXE) Simple.zip Deploy.zip 