# Introduction #

Follows is a list of libraries and/or software required to compile the project from its source files.  An IDE is not required, but highly recommended.

Please also note that it is not necessary to set up cross-compiling for this project, I simply compile for whatever OS I happen to be in at the time so don't stress about that.


# Details #

Required Libraries:
  * GLU
  * GLEW
  * GLFW

Required Libraries for Linux:
  * GLX

Currently all libraries except GLFW and GLEW are pre-installed with MSVC or MinGW GNU GCC compilers on Windows, though make sure to grab the up-to-date GLEXT.H, WGLEXT.h and GLXEXT.H from the opengl.org website.

To download the above libraries on Ubuntu based distributions for Linux:
```
sudo apt-get install libgl1-mesa-dev libglew-dev libglfw-dev
```
This should use your package installer to install the required libraries to your system including the necessary drivers.  On Linux once these are installed, compile the application via Code::Blocks project provided in the repo and it should "just work"

Windows only requires you to install GLEW and GLFW, to get the 32-bit binaries of these, you can go to their website and download them, install them to someplace like: "C:/glew-32" and "C:/glfw-32" and set up Code::Blocks to recognise those two directories as the base directory for $(#glew) and $(#glfw) global variables.

To add global variables to the Code::Blocks environment, or modify your variables:
  * Go to the Menu Bar, and click "Settings"
  * Browse down to "Global Variables..." click.
  * Make sure Current Set is set to "default"
  * On the right of Current Variable, click "New"
  * Enter "glfw"
  * This should now set the Current Variable as "glfw"
  * In the base field, supply the directory that is the root of the glfw library, for instance I installed glfw to: "C:/glfw-32"
  * Set the include and lib directories, they are absolute paths, not relative.
  * Repeat for GLEW

the Trespassing project is already configured to look in the include/lib directories supplied by the glfw and glew global variables, so all you need to do is supply them in your own IDE.

The reason we use the 32-bit versions of GLFW and GLEW is that MinGW by default is 32-bit only, you can get a copy of it built to make W64 binaries though if you want, I will supply more information on configuring that to work with Trespassing and how you can add it without modifying the existing 32-bit compiler.