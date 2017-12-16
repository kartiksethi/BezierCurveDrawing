/* 
 * File:   BezierDrawer.cpp
 * Author: tanmaya
 *
 * Created on 20 November, 2017, 3:45 PM
 */

#include "BezierDrawer.h"

BezierDrawer::BezierDrawer(int Steps)
{
    steps = Steps;
    curvePoints.reserve(steps + 1); //reserving to avoid repeated resizings
}

void BezierDrawer::deleteControl(int index)
{
    controlPoints.erase(controlPoints.begin() + index); //deleting the index
    make(); //making the curve again
}

void BezierDrawer::make()
{
    curvePoints.clear();
    GLdouble incr = 1.0 / steps;    
    for(GLdouble t = 0.0; t <= 1.0; t += incr) //sampling t at regular intervals
    {    
        curvePoints.push_back(deCasteljau(0, controlPoints.size() - 1, t)); // performing deCasteljau for each t
    }
}
void BezierDrawer::makeFromVector(std::vector< Point > ControlPoints)
{
    controlPoints = ControlPoints;
    make();
}

void BezierDrawer::add(Point p)
{
    controlPoints.push_back(p);
    GLdouble incr = 1.0 / steps;
    if(controlPoints.size() == 1) //if this is the first point, just fill the array with the point
    {
        for(GLdouble t = 0.0; t <= 1.0; t += incr)
        {    
            curvePoints.push_back(p);
        }
        return;
    }
    int i = 0;
    for(GLdouble t = 0.0; t <= 1.0; t += incr) //otherwise, you can use the already drawn curve
    {    
        curvePoints[i] = lerp(curvePoints[i], deCasteljau(1, controlPoints.size() - 1, t), t);
        i++;
    }   
}

Point BezierDrawer::lerp(Point p1, Point p2, GLdouble t)
{
    return make_pair(p1.first * (1 - t) + p2.first * t, p1.second * (1 - t) + p2.second * t); //linear interpolationg
}

Point BezierDrawer::deCasteljau(int start, int end, GLdouble t)
{
    std::vector < Point > temp(controlPoints); //array storing the intermediate points
    for(int i = end; i > start; i--) //lerping n (n - 1) / 2 times
    {
        for(int j = start; j < i; j++)
            temp[j] = lerp(temp[j], temp[j + 1], t);
    }
    return temp[start];    
}

