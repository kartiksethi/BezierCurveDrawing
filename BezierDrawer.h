/* 
 * File:   BezierDrawer.h
 * Author: tanmaya
 *
 * Created on 20 November, 2017, 3:45 PM
 */

#ifndef BEZIERDRAWER_H
#define BEZIERDRAWER_H

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

typedef std::pair<GLdouble, GLdouble> Point;
class BezierDrawer
{
public:
    int steps; //the number of steps for t
    std::vector < Point > controlPoints; //the array of control points
    std::vector < Point > curvePoints; //the array of the actual curvePoints
    /**
     * The constructor to make a curve drawer.
     * @param Steps The number of steps for the t value
     */
    BezierDrawer(int Steps);
    /**
     * Makes a new curve from the given vector of control points
     * @param ControlPoints The control points for the new curve
     */
    void makeFromVector (std::vector < Point > ControlPoints);
    /**
     * Makes the curve based on the stored control points.
     */
    void make();
    /**
     * Adds one point to the control points of the Bezier curve at the end
     * @param p The point to be added
     */
    void add (Point p);
    /**
     * Deletes the control point at the given index
     * @param index The index to be deleted
     */
    void deleteControl(int index);
private:
    /**
     * Linear interpolate between two points
     * @param p1 The first point
     * @param p2 The second point
     * @param t The weight of the second point
     * @return The created point
     */
    Point lerp(Point p1, Point p2, GLdouble t);
    /**
     * Applies the deCasteljau's algorithm between the start and the end index of the controlPoints
     * @param start The starting index
     * @param end The ending index
     * @param t The t value
     * @return The generated point on the curve
     */
    Point deCasteljau(int start, int end, GLdouble t);
    
};

#endif /* BEZIERDRAWER_H */

