/* 
 * File:   main.cpp
 * Author: tanmaya
 *
 * Created on 20 November, 2017, 2:11 PM
 */

#include <cstdlib>
#include "Camera.h"
#include "BezierDrawer.h"
#include "SurfaceOfRevolution.h"

using namespace std;
/*
 * Utils
 */
Camera* C;
BezierDrawer* B;
bool track;
int dragPos;
/*
 * Params
 */
int width = 500; //width of the window
int height = 500; //height of the window
GLdouble curveColor[3] = {1.0, 0.0, 0.0}; //color of the Bezier curve
GLdouble controlColor[3] = {0.0, 0.0, 1.0}; //color of the Control polygon
GLdouble backColor[3] = {0.0, 0.0, 0.0}; //color of the background
double clickThresh = 50.0; //threshold for clicking distance
int steps = 10; //segments per Bezier curve
/**
 * The rendering function
 */
void draw()
{
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_STRIP); //drawing the bounding box
        glColor3d(controlColor[0], controlColor[1], controlColor[2]);
        for (auto point: B->controlPoints)
            glVertex2d(point.first, point.second);
    glEnd();
    glBegin(GL_LINE_STRIP); //drawing the curve
        glColor3d(curveColor[0], curveColor[1], curveColor[2]);
        for (auto point: B->curvePoints)
            glVertex2d(point.first, point.second);
    glEnd();    
    glutSwapBuffers();
}

/**
 * Computes the squared Euclidean distance between two points
 * @param p The first point
 * @param q The second point
 * @return The squared Euclidean distance
 */
double dist(Point p, Point q)
{
    return (p.first - q.first) * (p.first - q.first) + (p.second - q.second) * (p.second - q.second);
}

/**
 * Gets the closest point to the point p, with a threshold
 * @param p The reference point
 * @return The index of the closest point in B->controlPoints. -1 if none within threshold
 */
int getClosest(Point p)
{
    double min = std::numeric_limits<double>::max();
    int position = 0;
    for(int i = 0; i < B->controlPoints.size(); i++) //looping to find minimum dist
    {
        double d = dist(B->controlPoints[i], p);
        if(d < min)
        {
            min = d;
            position = i;
        }
    }
    if (min < clickThresh)
        return position;
    else
        return -1;
}
/**
 * Deletes the closest control point of B to p and remakes the curve
 * @param p The reference point
 */
void deleteClosest(Point p)
{
    
    int pos = getClosest(p);
    if(pos != -1)
        B->deleteControl(pos);
}
/**
 * The mouse click callback method
 * @param button The glut enum for left or right button
 * @param state Pressed or released
 * @param x x coordinate on the window
 * @param y y coordinate on the window
 */
void mouseClick(int button, int state, int x, int y)
{
    Point n = make_pair((double)x, height - (double)y);
    if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN) //addition
    {
        B->add(n);

    }
    else if(button ==  GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) //deletion
    {
        deleteClosest(n);
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) //start tracking mouse for dragging
    {
        int temp = getClosest(n);
        if(temp != -1)
        {
            track = true;
            dragPos = temp;
        }
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) //stop tracking
    {
        track = false;
    }
    glutPostRedisplay();
}

/**
 * Callback function for mouse movement
 * @param x The current x-coordinate of the mouse
 * @param y The current y-coordinate of the mouse
 */
void mouseMove(int x, int y)
{
    if(!track)
        return;
    Point p = make_pair((double)x, height - (double)y);
    B->controlPoints[dragPos] = p; //changing the control points
    B->make(); //making the curve again
    glutPostRedisplay();
}

/**
 * Handles key presses
 * @param key the keyboard input given by the user
 * @param x x coordinate of the input
 * @param y y coordinate of the input
 */
void keyPress(unsigned char key,int x,int y) {
    if(key=='s')
    {
        vector<vector<dvec3> > vertices;
        meshInit(B,vertices);
        makeMesh(vertices,10,"mesh.off");
    }
    glutPostRedisplay();
}

/**
 * Initializes the glut parameters and the GL camera
 */
void initGlut()
{
    int x = 0;
    glutInit(&x, nullptr);    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(width, height);
    glutCreateWindow("Bezier");
    C = new Camera(width, height);
    B = new BezierDrawer(steps);
    glClearColor(backColor[0], backColor[1], backColor[2], 0);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(keyPress);
}

int main(int argc, char** argv)
{   
    initGlut();
    glutDisplayFunc(draw);
    glutMainLoop();
}

