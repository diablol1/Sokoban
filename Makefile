COMPILER = g++
LINKER = g++
COMPILER_PARAMS = -std=c++17
LINKER_PARAMS = -lsfml-graphics -lsfml-window -lsfml-system

OBJS = obj/Counter.o obj/Game.o obj/main.o obj/Player.o obj/SceneManager.o obj/TextureCache.o obj/Tile.o

all: Sokoban

Sokoban: $(OBJS)
	$(LINKER) -o $@ $^ $(LINKER_PARAMS)

obj/%.o: src/%.cpp
	$(COMPILER) -c -o $@ $< $(COMPILER_PARAMS)

setup:
	mkdir obj

run:
	./Sokoban

clean:
	rm Sokoban
	rm obj/*
