CXX = g++
# OPTS = -std=c++17 -O2
OPTS = -std=c++17 -Og -g -Wall

LIBS = -lSDL2 -lSDL2_image
OBJ_NAME = Barbarian
FILES := color texture sprite random console input_handlers \
   	entity entity_actor entity_item entity_level \
	tile items monsters game_map pathfinding fov \
    engine engine_events engine_update engine_draw \
	engine_events_player engine_events_inventory engine_events_target engine_events_title \
	engine_events_levelup \
	engine_draw_game engine_draw_inventory engine_draw_target engine_draw_title \
	engine_draw_levelup \
	engine_fileIO \
	main
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
