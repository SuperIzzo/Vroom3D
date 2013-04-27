                        __  __                                          __    ____      
                       /\ \/\ \                                       /'__`\ /\  _`\    
                       \ \ \ \ \  _ __   ___     ___     ___ ___     /\_\L\ \\ \ \/\ \  
                        \ \ \ \ \/\`'__\/ __`\  / __`\ /' __` __`\   \/_/_\_<_\ \ \ \ \ 
                         \ \ \_/ \ \ \//\ \L\ \/\ \L\ \/\ \/\ \/\ \    /\ \L\ \\ \ \_\ \
                          \ `\___/\ \_\\ \____/\ \____/\ \_\ \_\ \_\   \ \____/ \ \____/
                           `\/__/  \/_/ \/___/  \/___/  \/_/\/_/\/_/    \/___/   \/___/ 
                        
                                                     v0.1
                                              Release:  26/04/2013

  						
SUMMARY
===============================
Vroom3D (Volume Rendering Object Oriented Machine) is a open source real-time 
direct volume rendering (DVR) engine, written in C++ and GLSL. It designed to
be minimal and portable library and is targeted primarily at games. 

The current features include:
* Volume rendering using 3D texture mapping
* CPU and GPU based gradient computation (normals)
* Basic Blinn-Phong and cell (toon) shading
* Basic and incomplete multi-isntance support and scene mamagent



1. Software Requirements
===============================

HARDWARE
-------------------------------
Vroom tries to be as low demanding on the hardware as possible, but the 
graphics card should support at least 3D texture mapping and shaders. The exact
GL shader language version is not known yet, but the more recent the better.
The demo has run on machines with 128MB of VRAM, the allowed dimensions for 3D
textures also vary from one graphics card to the next, the demo requires at 
least 128 voxels.

SOFTWARE
-------------------------------
The software has been developed and tested mostly on Windows 7, it is known to
have run successfully on Windows XP, but even though it does not directly call 
OS specific code no guarantees can be made that it will happily work on other
platforms.

The OpenGL library must be present and also make sure you have the appropriate 
graphics drivers installed.



2. Compiling the Source
===============================
The project has been built using Visual C++ 2010, but any newer version of VC++
should do.

You will are unlikely to be able to compile the source directly from the CD,
so you should copy at least the "src", "include", "test", "proj" and "sub" 
directories to a location you have write permissions to. And if you want to run
it you will also need to copy "data" as well.
The solution file can be found at:

                       <Vroom3D>\proj\MSVS_2010\Vroom3D.sln

Use the build button in VC++. The project is setup to run unit tests after it
has been compiled and some of them test OpenGL function calls, your built may 
fail if the machine you compile the sources does not meet the minimal 
requirements. If you build with the debug configuration the executable will be 
created in "bin\Debug", for the release it will be in "bin\Release".

When the demo is built, before you run it, make sure that "glew32.dll" can
be found by the executable. The simplest way to do this is to drop the library
in the same directory, or alternatively (and worse) you can add its destination
to the path. You can find the dll at:

                   <Vroom3D>\sub\glew-1.9.0-win32\bin\glew32.dll


3. Running the Demo
===============================



CONTROLS
Unfortunately the demo does not come with a fancy GUI and may be a little
hard and unintuitive to use. It is mainly controlled with key presses which 
change internal states and parameters. The control scheme is as follows:

*  [ up/down arrow keys ]    - change the number of slice
*  [ left/right arrow keys ] - change the spacing exponent (bundles more slices towards the camera)
*  [ M ]                     - alternates between 3 volume models:
                                  1) brick wall 2) a test volume 3) human head
*  [ L ]                     - toggles between shading modes
                                  1) off 2) Blinn-Phong 3) cell (toon) shading
*  [ N ]                     - shows the normal map of the volume
*  [ B ]                     - draws a bounding box around the volume
*  [ S ]                     - draws the outline of the polygon slices ( also drops the frame rate twice )



4. Dependencies
===============================
Eigen - linear algebra library
  Version:    3.1.1
  Authors:    Gael Guennebaud, Benoit Jacob and others
  Website:    http://eigen.tuxfamily.org/
  License:    MPL2 

GLEW - an OpenGL extension wrapper; easy access to non-core OpenGL functions
  Version:    1.9.0
  Authors:    Milan Ikits and Marcelo Magallon
  Website:    http://glew.sourceforge.net/
  License:    Modified BSD License
  
rapidxml -  tiny and fast XML parser implementation
  Version:    1.13
  Authors:    Marcin Kalicinski
  Website:    http://rapidxml.sourceforge.net/license.txt
  License:    MIT // Boost Software License 

SFML - Simple and Fast Multimedia Library
  Version:    2.0
  Authors:    Laurent Gomila
  Website:    http://www.sfml-dev.org/
  License:    zlib/png License
  
UnitTest++ - unit testing library framework
  Version:    1.4
  Authors:    Noel Llopis and Charles Nicholson
  Website:    http://unittest-cpp.sourceforge.net/
  License:    MIT
 
Yasper - a simple, small and portable smart pointer library
  Version:    1.04
  Authors:    Alex Rubinsteyn
  Website:    http://yasper.sourceforge.net/
  License:    zlib/libpng License
