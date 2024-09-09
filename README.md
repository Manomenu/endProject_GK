# End Project - robust 3D scene

---

## How to run
Download project with submodules: git clone --recurse-submodules <repo-url.git>. 

If it wasn't enough call also: git submodule update --init --recursive and git submodule update --remote --merge. 

Open Project folder in Visual Studio, open CMakeLists.txt and press Ctrl + S.
Then select endproject.exe project and compile & run it.
After creating exe file you can run it from Visual Studio or you can 
open endproject.exe file in endProject_GK/out/build/x64-Debug folder.

By default project is compiled in Release mode.

---

## Project intentions
I want to use <b>new</b> keyword only if it actually makes sense. 
Besides that I've decided to pass structs that have default constructor, and optionally <b>initialize</b> method.
Thanks to it I can set up class in a more flexible manner and don't have to implement unnecessary =operator overrides.

To organize my code I've decided to use Entity Component System style. It will help me later to run my code in parallel more easily and I can extend 
entities functionalities in a flexible manner.

I don't try to optimize things until it's necessary. 
I avoid abstractions and templates unless they will finally seems applicable in previously implemented code.

At the very begining I want to implement simple solutions, and later switch to more robust solution in an iterative manner.

---

## Description
3D scene:
- Animated car with tiltable lights
- 3 different cameras
- Multiple lights (spot & directional lights)
- City scene
- Day / Night mode
- Pausable motion
- Models loaded from files (glb and obj files)
- Customizable fog

---

## Showcase video

https://github.com/user-attachments/assets/d8245686-6353-4f6a-b6cc-e57a9988a692

