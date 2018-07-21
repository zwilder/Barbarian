CXX = g++
# -g For debugging flags, -O2 for optimization
OPTS = -std=c++17 -O2
# OPTS = -std=c++17 -Og -g -Wall
LIBS = -lSDL2 -lSDL2_image

FILES := color texture sprite random console input_handlers entity tile game_map pathfinding fov engine 
OBJS := $(FILES:=.o)
SRC := $(OBJS:.o=.cpp)
VPATH = ./src:./include

OBJ_NAME = Barbarian

.PHONY: clean main

all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS) main.o
	$(CXX) $(OPTS) -o $(OBJ_NAME) $(OBJS) main.o $(LIBS)

$(OBJS): %.o: %.cpp %.hpp
	$(CXX) $(OPTS) -c $< -o $@

main: main.o
	$(CXX) $(OPTS) -c src/main.cpp -o main.o

clean:
	rm *.o
