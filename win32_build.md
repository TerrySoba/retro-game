# Building the game on Windows

Download the 64bit version of [Msys2](http://www.msys2.org/).
Then 32bit version may also work, but this in untested.

Update the package database and core system packages with:
```
pacman -Syu
```
Close msys2 window afterwards.

Start "MSYS2 MinGW 64-bit" from the startmenu.
```
pacman -Su
```

Install mingw64 toolchain:
```
pacman -S mingw-w64-x86_64-toolchain
```

Install Boost using the following commandline:
```
pacman -S mingw64/mingw-w64-x86_64-boost
```

Install libmikmod:
```
pacman -S mingw64/mingw-w64-x86_64-libmikmod
```

Install cmake
```
pacman -S mingw64/mingw-w64-x86_64-cmake
```

Install make
```
pacman -S make
```

Install git
```
pacman -S git
```

Now create build directory and run cmake
```
git clone https://github.com/TerrySoba/retro-game
mkdir retro-game-build
cd retro-game-build
cmake ../retro-game -G"MSYS Makefiles"
make
```

Now the game should have been built.