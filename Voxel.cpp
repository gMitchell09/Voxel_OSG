//
//  Voxel.cpp
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/27/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#include "Voxel.h"

Voxel::Voxel(osg::Vec3 dim, BlockType blockType) : _dim(dim), _blockType(blockType) {
	this->initGeom();
}

Voxel::Voxel() : _dim(osg::Vec3d(1, 1, 1)), _geom(new osg::Geometry) {
	this->initGeom();
}

void Voxel::initGeom() {
	std::cout << "Constructing Voxel" << std::endl;
	
	osg::ref_ptr<osg::Vec3Array> cubeVertices = new osg::Vec3Array;
    cubeVertices->push_back( osg::Vec3( 0,       0,        0) ); // bottom front left
    cubeVertices->push_back( osg::Vec3(_dim.x(), 0,        0) ); // bottom front right
    cubeVertices->push_back( osg::Vec3(_dim.x(), _dim.y(), 0) ); // bottom back right
    cubeVertices->push_back( osg::Vec3( 0,       _dim.y(), 0) ); // bottom back left
	
	cubeVertices->push_back( osg::Vec3( 0,       0,        _dim.z()) ); // top front left
    cubeVertices->push_back( osg::Vec3(_dim.x(), 0,        _dim.z()) ); // top front right
    cubeVertices->push_back( osg::Vec3(_dim.x(), _dim.y(), _dim.z()) ); // top back right
    cubeVertices->push_back( osg::Vec3( 0,       _dim.y(), _dim.z()) ); // top back left
	
	
    _geom->setVertexArray( cubeVertices.get() );
	
	osg::ref_ptr<osg::DrawElementsUInt> cubeBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    cubeBase->push_back(3);
    cubeBase->push_back(2);
    cubeBase->push_back(1);
    cubeBase->push_back(0);
    _geom->addPrimitiveSet(cubeBase.get());
	
	osg::ref_ptr<osg::DrawElementsUInt> cubeTop = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	cubeTop->push_back(7);
	cubeTop->push_back(6);
	cubeTop->push_back(5);
	cubeTop->push_back(4);
	_geom->addPrimitiveSet(cubeTop.get());
	
	osg::ref_ptr<osg::DrawElementsUInt> cubeFront = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	cubeFront->push_back(4);
	cubeFront->push_back(0);
	cubeFront->push_back(1);
	cubeFront->push_back(5);
	_geom->addPrimitiveSet(cubeFront.get());
	
	osg::ref_ptr<osg::DrawElementsUInt> cubeBack = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	cubeBack->push_back(7);
	cubeBack->push_back(3);
	cubeBack->push_back(2);
	cubeBack->push_back(6);
	_geom->addPrimitiveSet(cubeBack.get());
	
	osg::ref_ptr<osg::DrawElementsUInt> cubeLeft = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	cubeLeft->push_back(7);
	cubeLeft->push_back(3);
	cubeLeft->push_back(0);
	cubeLeft->push_back(4);
	_geom->addPrimitiveSet(cubeLeft.get());
	
	osg::ref_ptr<osg::DrawElementsUInt> cubeRight = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	cubeRight->push_back(5);
	cubeRight->push_back(1);
	cubeRight->push_back(2);
	cubeRight->push_back(6);
	_geom->addPrimitiveSet(cubeRight.get());
	
    //Declare and load an array of Vec4 elements to store colors.
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f) ); //index 4 yellow
	colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f) ); //index 5 purple
	colors->push_back(osg::Vec4(1.0f, 0.5f, 0.5f, 1.0f) ); //index 6 something
	colors->push_back(osg::Vec4(0.0f, 0.4f, 0.8f, 1.0f) ); //index 7 something else
	
    //The next step is to associate the array of colors with the geometry,
    //assign the color indices created above to the geometry and set the
    //binding mode to _PER_VERTEX.
	
    _geom->setColorArray(colors.get());
    _geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	this->addDrawable(_geom);
}