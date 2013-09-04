//
//  Voxel.cpp
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/27/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#include "Voxel.h"
#include "MarchingCubes.h"

Voxel::Voxel(osg::Vec3 dim, osg::Vec3d pos, int cornerWeight, BlockType blockType) : _geode(new osg::Geode()), _position(pos), _blockType(blockType), _cornerWeight(cornerWeight), _geom(new osg::Geometry) {
	this->initGeom(dim);
}

Voxel::Voxel(osg::Vec3 dim, osg::Vec3d pos, BlockType blockType) : _geode(new osg::Geode()), _position(pos), _blockType(blockType), _geom(new osg::Geometry), _cornerWeight(0) {
	this->initGeom(dim);
}

Voxel::Voxel() : _geode(new osg::Geode()), _position(osg::Vec3d(0 ,0, 0)), _geom(new osg::Geometry), _blockType(BlockType::BlockType_Default), _cornerWeight(0) {
	this->initGeom(osg::Vec3d(1, 1, 1));
}

void Voxel::initGeom(osg::Vec3d dim) {
	std::cout << "Constructing Voxel" << std::endl;
	
	osg::ref_ptr<osg::PositionAttitudeTransform> xForm = new osg::PositionAttitudeTransform();

	xForm->setPosition( this->_position );
	this->addChild(xForm);
	xForm->addChild(this->_geode);

	
	//int Polygonise(GRIDCELL grid, double isolevel, TRIANGLE *triangles);
	GRIDCELL grid;
	grid.p[0] = osg::Vec3( 0,       0,        0); // bottom front left
    grid.p[1] = osg::Vec3( dim.x(), 0,        0); // bottom front right
    grid.p[2] = osg::Vec3( dim.x(), dim.y(), 0); // bottom back right
    grid.p[3] = osg::Vec3( 0,       dim.y(), 0); // bottom back left
	
	grid.p[4] = osg::Vec3( 0,       0,        dim.z()); // top front left
    grid.p[5] = osg::Vec3( dim.x(), 0,        dim.z()); // top front right
    grid.p[6] = osg::Vec3( dim.x(), dim.y(),  dim.z()); // top back right
    grid.p[7] = osg::Vec3( 0,       dim.y(),  dim.z()); // top back left
	
	grid.val[0] = _cornerWeight & 1;
	grid.val[1] = _cornerWeight & 2;
	grid.val[2] = _cornerWeight & 4;
	grid.val[3] = _cornerWeight & 8;
	grid.val[4] = _cornerWeight & 16;
	grid.val[5] = _cornerWeight & 32;
	grid.val[6] = _cornerWeight & 64;
	grid.val[7] = _cornerWeight & 128;
	
	TRIANGLE triangles[5];
	
	int nTri = Polygonise(grid, 0.5, triangles);
	
	std::cout << nTri << " triangles to draw" << std::endl;
	
	osg::ref_ptr<osg::Vec3Array> vertexArray = new osg::Vec3Array;
	for(int i = 0; i < nTri; i++) {
		vertexArray->push_back(triangles[i].p[0]);
		vertexArray->push_back(triangles[i].p[1]);
		vertexArray->push_back(triangles[i].p[2]);
	}
	
	_geom->setVertexArray( vertexArray );
		
	osg::ref_ptr<osg::DrawElementsUInt> tri = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	
	for(int i = 0; i < nTri; i++)
	{
		tri->push_back(i * 3);
		tri->push_back(i * 3 + 1);
		tri->push_back(i * 3 + 2);
	}
	
	_geom->addPrimitiveSet(tri.get());
	
	
    //Declare and load an array of Vec4 elements to store colors.
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
	for(int i = 0; i < nTri; i++) {
		colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
		colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
		colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
	}
	
    //The next step is to associate the array of colors with the geometry,
    //assign the color indices created above to the geometry and set the
    //binding mode to _PER_VERTEX.
	
    _geom->setColorArray(colors.get());
    _geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	this->_geode->addDrawable(_geom);
}

Voxel::~Voxel() {
	
}
