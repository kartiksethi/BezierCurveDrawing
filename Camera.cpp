/* 
 * File:   Camera.cpp
 * Author: tanmaya
 *
 * Created on 20 November, 2017, 2:12 PM
 */
#include "Camera.h"

Camera::Camera(int Width, int Height)
{
    width = Width;
    height = Height;
    setModelView(dvec3(-1, 0, 5), dvec3(-1, 0, 0), dvec3(0, 1, 0));
    setProjection(45, width/height, 0.1, 50.0);
    enable_key = true;
    is2D = false;
    to2D();
}

void Camera::to2D()
{
    if(is2D)
        return;
    glGetDoublev(GL_PROJECTION_MATRIX, saved_projection);
    glGetDoublev(GL_MODELVIEW_MATRIX, saved_modelview);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    glOrtho(0, width, 0, height, -1, 1);
    enable_key = false;
    is2D = true;
}

void Camera::to3D()
{
    if(!is2D)
        return;
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(saved_modelview);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(saved_projection);
    is2D = false;
}

void Camera :: setProjection(double ViewAngle, double Aspect, double NearDist, double FarDist)
{
    viewAngle = ViewAngle;
    aspect = Aspect;
    nearDist = NearDist;
    farDist = FarDist;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(viewAngle, aspect, nearDist, farDist);
}

void Camera::setModelView(dvec3 Eye, dvec3 Look, dvec3 Up)
{
    eye = Eye;
    look = Look;
    up = Up;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
}

void Camera::move(dvec3 displacement)
{
    if(!enable_key)
        return;
    GLdouble temp[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, temp);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-displacement.x, -displacement.y, -displacement.z);
    glMultMatrixd(temp);
}

void Camera:: roll(double angle)
{
    if(!enable_key)
        return;
    GLdouble temp[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, temp);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-angle, 1, 0, 0);
    glMultMatrixd(temp);
}

void Camera:: pitch(double angle)
{
    if(!enable_key)
        return;
    GLdouble temp[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, temp);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-angle, 0, 1, 0);
    glMultMatrixd(temp);
}

void Camera:: yaw(double angle)
{
    if(!enable_key)
        return;
    GLdouble temp[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, temp);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-angle, 0, 0, 1);
    glMultMatrixd(temp);
}