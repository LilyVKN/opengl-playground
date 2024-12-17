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
Per Lodstedt. Coulomb friction in twodimensional rigid body systems. *Zeitschrift fur Angewandte Mathematik und Mechanik*. 1981
Brian Vincent Mitrich. Impulse-based Dynamic Simulation of Rigid Body Systems. 1996