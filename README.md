# Do-The-Wave
A 2D OpenGL Visualization made using VS 2017

Recently, I picked up the OpenGL red book, so I've been wanting to really get better practice with it than before.  This project as a whole was just an experimentation seeing how far I can go with just 2 triangles, a simple pass-through vertex shader, and a custom fragment shader.  Everything uploaded is a Visual Studio 2017 solution, so hopefully there shouldn't be any problems, but all that should be needed are the additional includes and libraries from GLEW and GLFW.  Code's written to hopefully be cross platform, although as of now it is stuck at 1920 x 1080 as a resolution.

There's a macro defined in main.cpp to indicate the MAX_WAVES it grows to (should be greater than 1 to avoid weird stitching issues), as well as macros in the waves_frag shader to define the SCREEN_X and SCREEN_Y.  Should be able to support any resolution desired, although you may want to update the size of the window glfw generates.

A video of the program running can be found here: https://youtu.be/rXEgQhaaLUU