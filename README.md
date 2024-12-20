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
David Baraff. Fast Contact Force Computation for Non-penetrating Rigid Bodies. [Link](https://www.cs.cmu.edu/~baraff/papers/sig94.pdf)  
Brian Mitrich, John Canny. Impulse-based Simulation of Rigid Bodies. 1995. [Link](https://graphics.stanford.edu/courses/cs468-03-winter/Papers/ibsrb.pdf)  
Brian Vincent Mitrich. Impulse-based Dynamic Simulation of Rigid Body Systems. 1996. [Link](http://www.kuffner.org/james/software/dynamics/mirtich/mirtichThesis.pdf)  
David Stewart, J.C. Trinkle. An Implicit Time-Stepping Scheme for Rigid Body Dynamics with Coulomb Friction. 1996. [Link](https://foswiki.cs.rpi.edu/foswiki/pub/RoboticsWeb/LabPublications/STicra00.pdf)  
Michael Cline, Dinesh Pai. Post-Stabilization for Rigid Body Simulation with Contact and Constraints. 2003. [Link](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=476dfce4be549655938c499663af246702cbc781)  
Erin Catto. Iterative Dynamics with Temporal Coherence. 2005. [Link](https://box2d.org/files/ErinCatto_IterativeDynamics_GDC2005.pdf)  
Kenny Erleben. Physics-Based Animation. 2005. [Link](https://iphys.wordpress.com/wp-content/uploads/2020/01/erleben.ea05.pdf)  
Kenny Erleben. Numerical Methods for Linear Complementarity Problems in Physics-based Animation. 2013 [Link](http://image.diku.dk/kenny/download/erleben.13.siggraph.course.notes.pdf)  
[Video](https://www.youtube.com/watch?v=SHinxAhv1ZE)  

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