[![Build Status](https://travis-ci.org/TerrySoba/retro-game.svg?branch=master)](https://travis-ci.org/TerrySoba/retro-game)

# retro-game
Experiments using [libretro](https://www.libretro.com/).

This is supposed to become a simple arcade style game.
It is also supposed to become a tutorial on how to design a
simple game using libretro.

##Building the Game
The game is being developed using Linux.
It may or may not run using Windows.

The game is built using cmake.
In the base directory type:
```
cmake . && make
```
Now the game should be built.

For windows follow these instructions: [Building on Windows](win32_build.md)

##Running the Game
To run the game you need to install [Retroarch](https://www.libretro.com/index.php/retroarch-2/).
On Ubuntu type:
```
sudo apt-get install retroarch
```

When retroarch is installed, you can play the game using the commandline
```
retroarch -L libRetroGame.so
```
while in the build directory.


##Using Blender to create Pixel Graphics
I mainly use [Blender](http://blender.org) to create the assets for the game.
Here is a small [tutorial](./doc/blender_tutorial.md) on how to use Blender to create pixel graphics.
