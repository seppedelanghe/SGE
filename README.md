# Simple Game Engine
A C++ Game Engine project to make learning C++ fun.


# Development
## Requirements

- `g++` with C++ 14
- SDL2 with image and TTF support
    - `SDL2`
    - `SDL2_image`
    - `SDL2_ttf`

## Installation

### SDL2

__Linux__
https://wiki.libsdl.org/SDL2/Installation#linuxunix

__MacOS__
```bash
brew install SDL2
brew install SDL2_image
brew install SDL2_ttf
```

__Windows__
https://wiki.libsdl.org/SDL2/Installation#windows_xpvista7810


### Makefile
Ensure to edit the `makefile` is updated with the correct SDL2 paths.


### Building

Run `make` to build all files and 

```bash
make
```

### Running
```bash
./main
```




# Folders

## ECS
__Entity component system__
Contains all code for entities and components to link to them.

## IS
__Interaction systems__
Contains all code to create systems to interact with:
- Map generation
- UI






# Game Development

## Map

Maps are tile maps defined in text based files with a fixed structure. \
The structure is as following: `texture_x,texture_y:collision_layer`
With a semicolon in between each tile as a seperator: `;`

A map of 4x4 would look something like this:
```
1,0:1;1,0:1;1,0:1;1,0:1;
1,0:1;2,3:0;2,3:1;1,0:1;
1,0:1;2,3:0;2,3:1;1,0:1;
1,0:1;1,0:1;1,0:1;1,0:1;
```
