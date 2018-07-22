CXX = g++
# OPTS = -std=c++17 -O2
OPTS = -std=c++17 -Og -g -Wall

LIBS = -lSDL2 -lSDL2_image
OBJ_NAME = Barbarian
FILES := color texture sprite random console input_handlers entity tile game_map pathfinding fov engine main
OBJS := $(FILES:=.o)
SRC := $(OBJS:.o=.cpp)
DEP := $(FILES:=.d)

VPATH = ./src:./include

.PHONY: clean

all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	$(CXX) $(OPTS) -o $(OBJ_NAME) $(OBJS) $(LIBS)

$(OBJS): %.o: %.cpp %.d
	$(CXX) $(OPTS) -c $< -o $@

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -M $(OPTS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEP)

clean:
	rm *.o *.d
