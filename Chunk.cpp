//
//  Chunk.cpp
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/28/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#include "Chunk.h"

Chunk::Chunk(std::vector<osg::ref_ptr<osg::Node>>& voxels) : _voxels(voxels) {
	for(auto i = voxels.begin(); i != voxels.end(); i++) {
		this->addChild(i.base()->get());
	}
}

Chunk::~Chunk() {
	
}