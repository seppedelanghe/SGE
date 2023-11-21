CC = g++
VERSION = c++17

SDL2_PATH = /opt/homebrew/Cellar/sdl2/2.28.5/
SDL2_IMG_PATH = /opt/homebrew/Cellar/sdl2_image/2.6.3_2/
SDL2_TTF_PATH = /opt/homebrew/Cellar/sdl2_ttf/2.20.2/

SDL2_INCLUDE_DIRS = -I$(SDL2_PATH)include/SDL2 -I$(SDL2_IMG_PATH)include/SDL2 -I$(SDL2_TTF_PATH)include/SDL2
INCLUDE_DIRS = -I./ECS
SDL2_LINK_DIRS = -L$(SDL2_PATH)lib -L$(SDL2_IMG_PATH)lib -L$(SDL2_TTF_PATH)lib
LINK_DIRS = 
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = --std=$(VERSION)
CPP_SRC = $(wildcard *.cpp) $(wildcard ECS/*.cpp) $(wildcard ECS/A/*.cpp) $(wildcard ECS/G/*.cpp) $(wildcard services/*.cpp)
OBJ_FILES = $(CPP_SRC:.cpp=.o)


main: $(OBJ_FILES)
	export DCMAKE_EXPORT_COMPILE_COMMANDS=1
	$(CC) -o $@ $^ $(SDL2_INCLUDE_DIRS) $(INCLUDE_DIRS) $(SDL2_LINK_DIRS) $(LINK_DIRS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(SDL2_INCLUDE_DIRS) $(SDL2_LINK_DIRS) $(INCLUDE_DIRS) -c -o $@ $<

obj_clean:
	rm -rf $(OBJ_FILES)

clean: obj_clean
	rm -f main

run: main obj_clean
	./main
