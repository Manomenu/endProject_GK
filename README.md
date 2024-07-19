# End Project - robust 3D scene

---

## Project intentions
I want to use <b>new</b> keyword only if it actually makes sense. 
Besides that I've decided to pass structs that have default constructor, and optionally <b>initialize</b> method.
Thanks to it I can set up class in a more flexible manner and don't have to implement unnecessary =operator overrides.

To organize my code I've decided to use Entity Component System style. It will help me later to run my code in parallel more easily and I can extend 
entities functionalies in a flexible manner.

I don't try to optimize things until it's necessary. 
I avoid abstractions and templates unless they will finally seems applicable in previously implemented code.

At the very begining I want to implement simple solutions, and later switch to more robust solution in an iterative manner.
For example I will later try to switch from basic renderer to ray casting rendering.

## Description
3D scene


