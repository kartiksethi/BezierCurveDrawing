//
// Created by kartik on 21/11/17.
//

#ifndef BEZIER_DRAWING_SURFACEOFREVOLUTION_H
#define BEZIER_DRAWING_SURFACEOFREVOLUTION_H

#include "BezierDrawer.h"
#include "Mesh.h"
#include <bits/stdc++.h>

/**
 * Function to convert the 2d coordinates of the curve points to 3d
 * @param B refers to the BezierDrawer object (curve)
 * @param vertices refers to the vector containing all the vertices and their modified points (after rotations)
 */
void meshInit(BezierDrawer* B, vector<vector<dvec3> > &vertices)
{
    vector<dvec3> temp;
    for(auto point: B->curvePoints)
    {
        dvec3 p1 = {point.first, point.second, 0};
        temp.push_back(p1);
    }
    vertices.push_back(temp);
}

/**
 * Function to get a rotate matrix based on the given angle
 * @param rotate_mat refers to the rotation matrix which will be used for transformation
 * @param angle refert to the angle using which rotation matrix will be calculated
 */
void getRotateMat(dmat3 &rotate_mat, double angle)
{
    rotate_mat[0][0] = cos(radians(angle));
    rotate_mat[0][1] = 0.0;
    rotate_mat[0][2] = sin(radians(angle));
    rotate_mat[1][0] = 0.0;
    rotate_mat[1][1] = 1.0;
    rotate_mat[1][2] = 0.0;
    rotate_mat[2][0] = -sin(radians(angle));
    rotate_mat[2][1] = 0.0;
    rotate_mat[2][2] = cos(radians(angle));
}

/**
 * Function to get the updated coordinates of each vertex after subsequent rotations
 * @param vertices refers to the vector containing all the vertices and their modified points (after rotations)
 * @param rotate_mat refers to the rotation matrix which will be used for transformation
 */
void updateVertices(vector<vector<dvec3> > &vertices, dmat3 rotate_mat)
{
    long size = vertices.size();
    vector<dvec3> new_points;
    vector<dvec3> previous_points (vertices[size-1].begin(), vertices[size-1].end());
    for(auto point: previous_points)
    {
        dvec3 temp_point = dvec3(point.x, point.y, point.z);
        dvec3 transformed_point = rotate_mat * temp_point;
        dvec3 trans_point = {transformed_point[0], transformed_point[1], transformed_point[2]};
        new_points.push_back(trans_point);
    }
    vertices.push_back(new_points);
}

/**
 * Function to create the mesh using the vertices' coordinates calculated above
 * @param vertices refers to the vector containing all the vertices and their modified points (after rotations)
 * @param increment refers to the increment in the angle of rotation
 * @param filename refers to the final output filename
 */
void makeMesh(vector<vector<dvec3> > &vertices, double increment, string filename)
{
    Mesh m;
    // Iterating over degree from 1 to 360
    for(double angle = increment; angle < 360; angle+= increment)
    {
        dmat3 rotate_mat(0.0f);
        getRotateMat(rotate_mat, increment);
        updateVertices(vertices, rotate_mat);
    }
    
    //add vertices to the mesh
    for (auto &vertice : vertices) {
        for (long j = 0; j < vertice.size(); ++j) {
            m.addPoint(vertice[j]);
        }
    }

    vertices.push_back(vertices[0]); //finishing the mesh by adding the initial points

    //add polygons to the mesh by converting them into a series of triangles
    for (long i = 0; i < vertices.size()-1; ++i) {
        for (long j = 0; j < vertices[i].size() - 1; ++j) {
            vector<long> triangle1;
            triangle1.push_back(m.getVertexIndex(vertices[i][j]));
            triangle1.push_back(m.getVertexIndex(vertices[i][j+1]));
            triangle1.push_back(m.getVertexIndex(vertices[i+1][j]));

            vector<long> triangle2;
            triangle2.push_back(m.getVertexIndex(vertices[i+1][j]));
            triangle2.push_back(m.getVertexIndex(vertices[i][j+1]));
            triangle2.push_back(m.getVertexIndex(vertices[i+1][j+1]));

            m.addPolygon(triangle1);
            m.addPolygon(triangle2);
        }
    }
    m.serialize(filename);
}

#endif //BEZIER_DRAWING_SURFACEOFREVOLUTION_H

