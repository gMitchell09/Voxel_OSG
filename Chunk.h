//
//  Chunk.h
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/28/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#ifndef __Voxel_Render__Chunk__
#define __Voxel_Render__Chunk__

#include <iostream>

#include <osg/Vec3ui>
#include <Vector>

#include "Voxel.h"

class Chunk {
	
public:
	Chunk(std::vector<Voxel>& voxels);
	
	~Chunk();
	
private:
	std::vector<Voxel> _voxels;
	osg::Vec3ui _dim;
};

#endif /* defined(__Voxel_Render__Chunk__) */
