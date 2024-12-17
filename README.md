## To-Dos

### General
- [ ] Move shader code to multiline header defines, compiled with Makefile

### Gilbert-Johnson-Keerthi Test Env
- [ ] Add user input to control model matrix
- [ ] Write support function for spheres
- [ ] Write support function for convex hull of vertices
- [ ] Calculate simplex to origin distance function

- [ ] Pass previous simplex to initialize next frame's collision detection
- [ ] Calculate minimum sphere of a convex hull
- [ ] Implement simple bounding volume hierarchy system

### Linear Complementarity Problem (LCP)
```
a = Af - b >= 0
f >= 0
f^T a = 0
```
Per Lodstedt. Coulomb friction in two-dimensional rigid body systems. *Zeitschrift fur Angewandte Mathematik und Mechanik*. 1981
Brian Vincent Mitrich. Impulse-based Dynamic Simulation of Rigid Body Systems. 1996. [Link](http://www.kuffner.org/james/software/dynamics/mirtich/mirtichThesis.pdf)

## Installation Instructions
```
sudo apt install x11-xserver-utils
sudo apt install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt install libglm-dev
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
sudo apt-get install libassimp-dev
```

GLAD
1. Head on to the [GLAD web service](https://glad.dav1d.de/).
2. Set the language to C++ and choose the specification as OpenGL.
3. In the API section, select "Version 3.3" for gl, make sure the profile is set to Core, and that the Generate a loader option is ticked.
4. Ignore the extensions and click Generate to produce the resulting library files.
5. GLAD, by now, should have provided you a zip file: glad.zip containing two folders(include and src).
6. Copy the folders inside include (glad and KHR) into your include(s) directory: `cp -R include/* /usr/include/`
7. Now copy the file glad.c inside the src folder to your current working directory.