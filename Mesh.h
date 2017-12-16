//
// Created by anikethjr on 20/11/17.
//

#ifndef BEZIER_DRAWING_MESH_H
#define BEZIER_DRAWING_MESH_H

#include <bits/stdc++.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace glm;

/**
 * Structure to store the color values of objects
 */
struct Color{
    double r,g,b,a;
};

/**
 * Class to model a polygonal mesh using pointer to vertex list representation
 */
class Mesh {
    vector<dvec3> vertices; //list of vertices
    vector<vector<long> > polygons; //list of polygons
    vector<Color> vertexColors;
    vector<Color> polygonColors;
    long edgeCount;

    /**
     * Calculates the edge count of the mesh
     */
    void calculateEdgeCount()
    {
        set<pair<long,long> > edges;
        for (int i = 0; i < polygons.size(); ++i) {
            for (int j = 0; j < polygons[i].size()-1; ++j) {
                if(edges.find(make_pair(polygons[i][j],polygons[i][j+1])) == edges.end() && edges.find(make_pair(polygons[i][j+1],polygons[i][j])) == edges.end())
                    edges.insert(make_pair(polygons[i][j],polygons[i][j+1]));
            }
        }
        edgeCount = edges.size();
    }

public:
    /**
     * Function to add a 3D point to the mesh
     * @param p point to be added
     * @param c color of the point
     */
    inline void addPoint(dvec3 p, Color c = {1,1,1,1}) {
        vertices.push_back(p);
        vertexColors.push_back(c);
    }

    /**
     * Function to add a polygon to the mesh
     * @param polygon set of vertices in anticlockwise order which define the polygon
     * @param c color of the polygon
     */
    inline void addPolygon(vector<long> polygon, Color c = {1,1,1,1}) {
        polygons.push_back(polygon);
        polygonColors.push_back(c);
    }

    /**
     * Fetch the vertex list of the input polygon
     */
    vector<long> getVertexListOfPolygon(long polygonNumber) {
        vector<long> temp;
        if(polygonNumber>=polygons.size())
            return temp;
        else
            return polygons[polygonNumber];
    }

    /**
     * Fetch the coordinates of input point
     */
    dvec3 getVertexCoordinates(long vertexNumber){
        dvec3 p;
        if(vertexNumber>=vertices.size())
            return p;
        else
            return vertices[vertexNumber];
    }

    /**
     * Returns the vertex number of the input point
     */
    long getVertexIndex(dvec3 p) {
        if (find(vertices.begin(), vertices.end(), p) == vertices.end())
            return -1;
        else
            return find(vertices.begin(), vertices.end(), p) - vertices.begin();
    }

    /**
     * Serialize the mesh in OFF format
     * @param filename name of the OFF file
     */
    void serialize(string filename)
    {
        Color c = {0.34, 0.5, 0.3, 0.3};
        calculateEdgeCount();
        fstream f(filename,ios::out);
        f<<"OFF"<<endl;
        f<<vertices.size()<<" "<<polygons.size()<<" "<<edgeCount<<endl;
        //Write the vertices and their colors
        for (int i = 0; i < vertices.size(); ++i) {
            f<<vertices[i].x<<" "<<vertices[i].y<<" "<<vertices[i].z<<endl;
        }
        //Write polygons and their colors
        for (int j = 0; j < polygons.size(); ++j) {
            f<<polygons[j].size()<<" ";
            for (long k : polygons[j]) {
                f<< k <<" ";
            }
            f<<c.r<<" "<<c.g<<" "<<c.b<<" "<<c.a<<" "<<endl;

        }
        f.close();
    }

};

#endif //BEZIER_DRAWING_MESH_H
