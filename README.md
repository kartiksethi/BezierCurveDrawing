# Interactive Bezier Curve Drawer

An OpenGL based implementation to render interactive Bezier Curves using [Geomview](www.geomview.org/).

We can create outputs similar to the following:

Steps to get the code running:

1. Install OpenGL, GLUT and GLM.

2. Clone the repo.

3. Compile the project using the command 
```
g++-5 *.cpp *.h -std=c++11 -lGL -lglut -lGLU
```

4. Run the executable. Left click to create a control point, right click on a control point and drag it so as to reposition it, middle mouse click on a control point to delete it and press 's' to generate a surface of revolution. The surface will be saved in the OFF format. You can use GEOMVIEW to visualize it.

Refer to the HTML documentation in the 'documentation' folder to learn more about the project. Code documentation generated using doxygen can be found in 'html' folder.

