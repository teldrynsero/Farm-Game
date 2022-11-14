SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDLLIBS=-lSDL2
# This path would need to change for every developer
#WINLOC=C:/Users/kayle/Desktop/Build
# Environment Variable GAMELOC is set in the development environment
WINLOC=$(GAMELOC)
SDLCFLAGS=-IC:\SDL2\include\SDL2 -Dmain=SDL_main
SDLLIBS=-LC:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf

SRCDIR=src
#IMGUI_DIR = ../..
SOURCES = $(SRCDIR)/Simple.cpp $(SRCDIR)/Exception.cpp $(SRCDIR)/imgui.cpp $(SRCDIR)/imgui_demo.cpp $(SRCDIR)/imgui_draw.cpp $(SRCDIR)/imgui_tables.cpp $(SRCDIR)/imgui_widgets.cpp $(SRCDIR)/imgui_impl_sdl.cpp $(SRCDIR)/imgui_impl_sdlrenderer.cpp $(SRCDIR)/imgui_stdlib.cpp
#SOURCES += /msys64/mingw64/include/imgui/imgui.cpp /msys64/mingw64/include/imgui/mgui_demo.cpp /msys64/mingw64/include/imgui/imgui_draw.cpp /msys64/mingw64/include/imgui/imgui_tables.cpp /msys64/mingw64/include/imgui/imgui_widgets.cpp
#SOURCES += /msys64/mingw64/include/imgui/backends/imgui_impl_sdl.cpp /msys64/mingw64/include/imgui/backends/imgui_impl_sdlrenderer.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

Simple.exe: $(SOURCES)
	g++ -std=c++17 $(SOURCES) -IC:\SDL2\include\SDL2 -LC:\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -o Simple

Simple: $(SRCS)
	g++ -g -Wall $(SDLCFLAGS) -o $@ $? $(SDLLIBS)

clean: 
	rm Simple.exe Simple



# cl /Zi /MD /I.. /I..\.. /I/msys64/mingw64/include/SDL2\include main.cpp ..\..\backends\imgui_impl_sdl.cpp ..\..\backends\imgui_impl_sdlrenderer.cpp ..\..\imgui*.cpp /FeDebug/example_sdl_sdlrenderer.exe /FoDebug/ /link /libpath:/msys64/mingw64/lib SDL2.lib SDL2main.lib /subsystem:console
SDLCFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDLLIBS=-lSDL2
# This path would need to change for every developer
#WINLOC=C:/Users/kayle/Desktop/Build
# Environment Variable GAMELOC is set in the development environment
WINLOC=$(GAMELOC)
WINSDLCFLAGS=-I$(WINLOC)/msys2/mingw64/include/SDL2/ -Dmain=SDL_main
WINSDLLIBS=-L$(WINLOC)/msys2/mingw64/lib/ -lmingw32 -mwindows -lSDL2main -lSDL2

SRCDIR=src
#IMGUI_DIR = ../..
SOURCES = $(SRCDIR)/Simple.cpp $(SRCDIR)/Exception.cpp $(SRCDIR)/imgui.cpp $(SRCDIR)/imgui_demo.cpp $(SRCDIR)/imgui_draw.cpp $(SRCDIR)/imgui_tables.cpp $(SRCDIR)/imgui_widgets.cpp $(SRCDIR)/imgui_impl_sdl.cpp $(SRCDIR)/imgui_impl_sdlrenderer.cpp $(SRCDIR)/imgui_stdlib.cpp
#SOURCES += /msys64/mingw64/include/imgui/imgui.cpp /msys64/mingw64/include/imgui/mgui_demo.cpp /msys64/mingw64/include/imgui/imgui_draw.cpp /msys64/mingw64/include/imgui/imgui_tables.cpp /msys64/mingw64/include/imgui/imgui_widgets.cpp
#SOURCES += /msys64/mingw64/include/imgui/backends/imgui_impl_sdl.cpp /msys64/mingw64/include/imgui/backends/imgui_impl_sdlrenderer.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

Simple.exe: $(SOURCES)
	g++ -std=c++17 $(SOURCES) -ID:/msys64/mingw64/include/SDL2 -LD:/msys64/mingw64/lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -o Simple

Simple: $(SRCS)
	g++ -g -Wall $(SDLCFLAGS) -o $@ $? $(SDLLIBS)

clean: 
	rm Simple.exe Simple



# cl /Zi /MD /I.. /I..\.. /I/msys64/mingw64/include/SDL2\include main.cpp ..\..\backends\imgui_impl_sdl.cpp ..\..\backends\imgui_impl_sdlrenderer.cpp ..\..\imgui*.cpp /FeDebug/example_sdl_sdlrenderer.exe /FoDebug/ /link /libpath:/msys64/mingw64/lib SDL2.lib SDL2main.lib /subsystem:console
