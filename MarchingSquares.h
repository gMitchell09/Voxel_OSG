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

class MarchingSquares {
public:
	static int* lookup_numPolys(int weight);
	static int* lookup_edgeConnectList(int weight);
};

#endif /* defined(__Voxel_Render__MarchingSquares__) */
