SDL_DIR = ../SDL/include

CC = g++

LIBS = -I$(SDL_DIR) -D_REENTRANT -lSDL2 -lSDL2_ttf -lSDL2_image

DEPS = BaseEngine.cpp FontManager.cpp TileManager.cpp BouncingBallMain.cpp BouncingBall.cpp DisplayableObject.cpp JPGImage.cpp Demo1Main.cpp Demo2Main.cpp Demo2Object.cpp Demo2TileManager.cpp Demo3Main.cpp Demo3Object.cpp Demo3ObjectFinished.cpp Demo3TileManager.cpp Demo4Main.cpp Demo4Object.cpp Demo4TileManager.cpp SimpleDemo.cpp

OUTPUT = ./a.out

build:
	$(CC) mainfunction.cpp $(DEPS) $(LIBS) -o $(OUTPUT) -std=c++11

