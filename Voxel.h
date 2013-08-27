//
//  Voxel.h
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/27/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#ifndef __Voxel_Render__Voxel__
#define __Voxel_Render__Voxel__

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/PositionAttitudeTransform>

#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventAdapter>

#include <osg/Vec4>

#include <osg/ref_ptr>
#include <osgText/Text>

#include <osg/Geode>

#include <sys/types.h>
#include <sys/sysctl.h>
#include <OpenGL/OpenGL.h> // for CoreOpenGL (CGL) for Multithreaded OpenGL Engine

#include <vector>
#include <osg/Array>
#include <iostream>

enum BlockType {

	BlockType_Default = 0,
	
	BlockType_Grass,
	BlockType_Dirt,
	BlockType_Water,
	BlockType_Stone,
	BlockType_Wood,
	BlockType_Sand,
	
	BlockType_NumTypes
};

class Voxel : public osg::Geode::Geode {
public:
	Voxel();
	Voxel(osg::Vec3 dim, BlockType blockType = BlockType_Default);
	
	
	bool isActive();
	void setActive(bool active);
private:
	
	void initGeom();
	bool _active;
	BlockType _blockType;
	
	osg::Vec3d _dim;
	osg::ref_ptr<osg::Geometry> _geom;
};

#endif /* defined(__Voxel_Render__Voxel__) */
