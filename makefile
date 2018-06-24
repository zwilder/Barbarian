CXX = g++
# -g For debugging flags, -O2 for optimization
OPTS = -std=c++11 -O2
LIBS = -lSDL2 -lSDL2_image

FILES := texture sprite random console input_handlers entity BSP game_map engine main
OBJS := $(FILES:=.o)
SRC := $(OBJS:.o=.cpp)
VPATH = ./src:./include

OBJ_NAME = Barbarian

all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	$(CXX) $(OPTS) -o $(OBJ_NAME) $(OBJS) $(LIBS)

$(OBJS): %.o: %.cpp
	$(CXX) $(OPTS) -c $< -o $@

clean:
	rm *o
