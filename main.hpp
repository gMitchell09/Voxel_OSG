//
//  main.hpp
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/20/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#ifndef Voxel_Render_main_hpp
#define Voxel_Render_main_hpp

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

#endif
