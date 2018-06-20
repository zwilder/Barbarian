# Barbarian!

A ~~Rogue~~Barbarian-like - created as an attempt to follow the famous [Python3 Roguelike tutorial](http://rogueliketutorials.com/) using C++ and SDL2.
The master branch has the current ('stable') version of the game, which is currently on Part 3 of the tutorial.

## Part 1
So I started this project using SFML - which is a fantastic and easy to use library, with tons of features. The goal of Part 0 was to get a console screen up,
and an '@' moving around. I thought about the idea of using SFML sprites directly on a simulated grid - but decided that although this was the easiest way 
to accomplish the '@' moving around, it would be beneficial to try and emulate a console much like libtcod does.

A console (defined in console.hpp) is a square grid of defined width and height, where each x,y coordinate pair is the location of a glyph. A glyph is an 
integer representing a character and a foreground/background color. Color (for now) is just a simple class (defined in color.hpp) with an integer representing
the r,g,b and alpha of a color.

Okay, with the console out of the way, it was time to make the 'engine' (defined in engine.hpp). So engine does three things primarily - handle input, update the
game, and draw it to the window ([the game loop - from Game Programming Patterns](http://gameprogrammingpatterns.com/game-loop.html)).

Handling input is easy... oh wait, the tutorial does some crazy magic with dictionaries. So, basically the idea of the dictionary is that it has a command 
and a value associated with that command. Sounds to me like a job for some bit flags, which would allow me to easily test if a command has a flag turned 
on and then check a value with it (The Action class - defined in input_handlers.hpp). Now, when checking keyboard input, I can just have a function 
return an Action, test the flags, and do whatever with the result. If needed, this allows multiple commands to be returned with one action - which is kinda cool.

Update! Well, update doesn't do anything yet. A good chunk of the game logic will eventually go here.

Draw is where some cool stuff happens. First, I have an array of rectangles, where each rectangle is a position on the font image of a character. What's
neat here is that the array contains 256 elements - the number of glyphs represented by a CP437 font image. This means that if an entity has a symbol represented
by an '@' symbol, I can reference the position on the font image by passing '@' as the index of the array! So the draw routine basically draws everything in the
game to the console, and then reads the console and translates that to the window using the window size and sprite size to position glyphs. 

With all that done, there is now an '@' symbol moving around the screen.

## Part 2
The big things in part are creating the Entity class and the GameMap class. The entity class is pretty simple so far - an entity has a glyph and a position. Nice and
easy. The GameMap is where things get fun - so I spent a bit more time on it. The tutorial uses simple booleans to check for tile values, again I decided that this
would be a good fit for bit flags - instead of checking if something blocksMovement and blocksLight and isDoor (or whatever) I could just do something simple like

```c++
int flag = blocksMovement | blocksLight | isDoor;
if(tile->checkFlag(flag)
{
    ///
}
...
bool checkFlag(int flag)
{
    return ((tileMask_ & flag) == flag);
}
```

GameMap (defined in game_map.hpp) is a grid of Tiles (defined in tile.hpp). Easy enough. For part 2, the game_map class generates a nice hardcoded wall for testing
Tiles and player movement. 

## Part 3
**Stay tuned for next week where I discuss dungeon generation, and the migration from SFML to SDL!**
