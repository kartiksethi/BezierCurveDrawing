/* 
 * File:   Camera.h
 * Author: tanmaya
 *
 * Created on 20 November, 2017, 2:12 PM
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#define PI 3.14159265

using namespace glm;
using namespace std;

class Camera
{
    private:
        dvec3 eye, look, up;
        GLdouble viewAngle, aspect, nearDist, farDist;
        bool enable_key, is2D;
        GLdouble width, height;
        GLdouble saved_projection[16];
        GLdouble saved_modelview[16];

    public:
        /**
         * Initializes a camera for the window
         * @param width The width of the window (pixels)
         * @param height The height of the window (pixels)
         */
        Camera(int Width, int Height);
        /**
         * Switches to 2D view
         */
        void to2D();
        /**
         * Restores the 3D view.
         */
        void to3D();
        /**
         * Sets up the model view matrix
         * @param eye Position of the eye
         * @param look dvec3 to look at from the eye
         * @param up The look-up vector
         */
        void setModelView(dvec3 eye, dvec3 look, dvec3 up);
        /**
         * Sets up the projection matrix
         * @param viewAngle Viewing angle
         * @param aspect Aspect ratio
         * @param nearDist near distance of the camera
         * @param farDist far distance of the camera
         */
        void setProjection(double ViewAngle, double Aspect, double NearDist, double FarDist);
        /**
         * Rotate around x
         * @param angle angle to rotate by
         */
        void roll(double angle);
        /**
         * Rotate around y
         * @param angle angle to rotate by
         */
        void pitch(double angle);
        /**
         * Rotate around z
         * @param angle angle to rotate by
         */
        void yaw(double angle);
        /**
         * Moves the camera by adding the given displacement
         * @param displacement Displacement vector which specifies additions to the camera position
         */
        void move(dvec3 displacement);
};

#endif