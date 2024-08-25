# The plan ahead:

Feature List:
 - Build system
 - Low-level utilities
 - Platform layer (Windows Linux and macOS)
 - Logger
 - File I/O
 - Application layer
 - Renderer API / Abstraction layer
 - Memory management API
 - Scenegraph / ECS
 - Profiling and debugging
 - Basic scripting support via hot-reloading
 - Physics system

Engine Architecture:
 - Platform Layer <Platform API, Console I/O, File I/O, Memory, Renderer API>
 - Core <Logger, Assertions, Data structures, Async File I/O, Memory Allocators, Parsers, Engine Config, Math + String Lib, RNG, Profiling, Localization>
 - Resource Management <Images, Materials, Meshes, Animations, World maps>
 - Front End Layer:
   - Renderer Front-end <GUI, Scenegraph, Camera, PostFX>
   - Renderer Back-end <API abstraction, Materials, Lighting, Shaders>
   - Audio 
   - Misc Stuff

