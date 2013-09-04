//
//  MarchingSquares.h
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/28/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#ifndef __Voxel_Render__MarchingSquares__
#define __Voxel_Render__MarchingSquares__

#include <iostream>
#include <osg/Vec3f>

#define ABS(x) (x<0?-x:x)

typedef struct {
	osg::Vec3f p[3];
} TRIANGLE;

typedef struct {
	osg::Vec3f p[8];
	double val[8];
} GRIDCELL;

/*
 Given a grid cell and an isolevel, calculate the triangular
 facets required to represent the isosurface through the cell.
 Return the number of triangular facets, the array "triangles"
 will be loaded up with the vertices at most 5 triangular facets.
 0 will be returned if the grid cell is either totally above
 of totally below the isolevel.
 */
osg::Vec3f VertexInterp(double isolevel, osg::Vec3f p1, osg::Vec3f p2, double valp1, double valp2);
int Polygonise(GRIDCELL grid, double isolevel, TRIANGLE *triangles);

class MarchingCubes {
public:
	static int* lookup_numPolys(int weight);
	static int* lookup_edgeConnectList(int weight);
};

#endif /* defined(__Voxel_Render__MarchingSquares__) */
