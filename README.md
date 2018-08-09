# Barbarian!

A ~~Rogue~~Barbarian-like - created as an attempt to follow the famous [Python3 Roguelike tutorial](http://rogueliketutorials.com/) using C++
and SDL2 as part of the [r/roguelikedev 2018 Tutorial Tuesday Challenge](https://www.reddit.com/r/roguelikedev/wiki/python_tutorial_series).

The master branch has the current ('stable') version of the game, which is currently finished with Part 13 of the tutorial, you can see the source for each
part by checking the tags under branches.

I'll be updating [the blog](https://wsl-blog.com) with my thoughts and rambles about this project.

- [Week 1: Parts 0-2](https://wsl-blog.com/posts/2018-06-20-the-roguelike-tutorial-week1/): Setting up the project, getting the `@` moving,
  setting up the map.
- [Week 2: Parts 3](https://wsl-blog.com/posts/2018-06-25-the-roguelike-tutorial-week2/): The switch to SDL, dungeon generation.
- [Week 3: Part 4](https://wsl-blog.com/posts/2018-07-02-the-roguelike-tutorial-week3/): FoV and Bresenham's line drawing.
- [Week 3b: Part 5](https://wsl-blog.com/posts/2018-07-10-the-roguelike-tutorial-week3b/): Adding entities, scheduling and pathfinding.
- [Week 4: Part 6-7](https://wsl-blog.com/posts/2018-07-18-the-roguelike-tutorial-week4/): Combat and a (rough) UI!
- [Week 5a: Part 8](https://wsl-blog.com/posts/2018-07-24-the-roguelike-tutorial-week5a/): Items and inventory!
- [Week 5b: Part 9](https://wsl-blog.com/posts/2018-07-31-the-roguelike-tutorial-week5b6/): Targeting functions and spells 
- [Week 6: Part 10-11](https://wsl-blog.com/posts/2018-07-31-the-roguelike-tutorial-week5b6/): Saving and player advancement 
- Week 7: Part 12-13: Coming soon!

**Stay tuned for next week!**

### Building Barbarian! From Source
So far, the build process has only been tested on Arch Linux. For most flavors of Linux, building should look like this:
- Make sure you have the SDL2 libraries installed from your package manager
- Open a terminal window, and navigate to your Downloads directory
- `git clone https://github.com/zwilder/barbarian`
- `cd Barbarian`
- `make` -- Tip: add the `-j` flag with the number of threads you want to speed up compile time (ie `-j4`)
- `make clean` -- This is optional, but will remove all the random build files cluttering the directory after make 

Adding compile instructions for other operating systems will be the first thing I tackle after the 7 week challenge is over.

### Playing the Game
- Move the player with the VI keys, the number pad, or the arrow keys
- `i` Inventory: Open your inventory, and then the letter corresponding to the item you wish to **use**
- `d` Drop: Open your inventory, and then the letter corresponding to the item you wish to **drop**
- `g` Get: Pickup an item
- `<shift>+ l` Look: Use the movement keys to look around, `Enter` or `Escape` to exit look mode 
- `F1` Fullscreen mode (may be wonky - again, haven't tested on anything other than Arch Linux)
- `<shift>+q` or `<ctrl>+q` Quit
- The game saves on quitting. Select `Load Game` from the main menu to continue!
