# The plan ahead:

## August 21, 2024:
This will be a game engine, which I know nothing about and plan to learn along the way. I will be
writing this in C/C++. My target environemtn for now will be MacOS, if I ever get this thing to work
however, I would try to add in cross platform support in the distant future. I want to write my own
API's for all low level computations pertaining to things like graphics rendering and object collision
and engine physics. However I do not want to write a 3D graphics API from scratch. Instead I will use
the OpenGL frame work for my front end rendering for now, but eventually probably move onto something
like Vulcan for better performance. I am for now not planning on using visual studio, so I'll have to 
set up Cmake builds for everything which I'm not looking forward to but I don't think I have another
option. I do not want to destroy my system with Clion either!

Components planned for now:
- Main entry point
- Main API for the engine
- Window manager to handle inputs and events
- Graphics renderer
- Some sort of graphics rendering abstraction (future: enable cross-platform rendering)
- Debugging (logging, unit testing, profiling)
- Scripting support
- Memory allocation and tracking
- Entity component system (ECS)
- File IO, VFS
- Physics engine
- Build systems for 3D models
