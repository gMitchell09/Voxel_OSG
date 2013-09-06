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
	osg::Vec3d normals[5];
	
	int nTri = Polygonise(grid, 0.5, triangles);
	
	std::cout << nTri << " triangles to draw" << std::endl;
	
	osg::ref_ptr<osg::Vec3Array> vertexArray = new osg::Vec3Array;
	for(int i = 0; i < nTri; i++) {
		vertexArray->push_back(triangles[i].p[0]);
		vertexArray->push_back(triangles[i].p[1]);
		vertexArray->push_back(triangles[i].p[2]);
		
		vertexArray->push_back(triangles[i].p[0]);
		vertexArray->push_back(triangles[i].p[1]);
		vertexArray->push_back(triangles[i].p[2]);
		
		normals[i] = osg::Vec3d( (triangles[i].p[1].y() - triangles[i].p[0].y()) * (triangles[i].p[2].z() - triangles[i].p[0].z()) - (triangles[i].p[2].y() - triangles[i].p[0].y()) * (triangles[i].p[1].z() - triangles[i].p[0].z()),
								 (triangles[i].p[1].z() - triangles[i].p[0].z()) * (triangles[i].p[2].x() - triangles[i].p[0].x()) - (triangles[i].p[1].x() - triangles[i].p[0].x()) * (triangles[i].p[2].z() - triangles[i].p[0].z()),
								 (triangles[i].p[1].x() - triangles[i].p[0].x()) * (triangles[i].p[2].y() - triangles[i].p[0].y()) - (triangles[i].p[2].x() - triangles[i].p[0].x()) * (triangles[i].p[1].y() - triangles[i].p[0].y()));
		std::cout << "Normal: (" << normals[i].x() << ", " << normals[i].y() << ", " << normals[i].z() << ")" << std::endl;
	}
	
	_geom->setVertexArray( vertexArray );
		
	osg::ref_ptr<osg::DrawElementsUInt> tri = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	osg::ref_ptr<osg::DrawElementsUInt> edges = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	
	for(int i = 0; i < nTri; i++)
	{
		tri->push_back(i * 6);
		tri->push_back(i * 6 + 1);
		tri->push_back(i * 6 + 2);
		
		edges->push_back(i * 6 + 3);
		edges->push_back(i * 6 + 4);
		edges->push_back(i * 6 + 5);
	}
	
	_geom->addPrimitiveSet(tri.get());
	_geom->addPrimitiveSet(edges.get());
	
    //Declare and load an array of Vec4 elements to store colors.
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
	for(int i = 0; i < nTri; i++) {
//		colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
//		colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
//		colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
		if(normals[i] == osg::Vec3d(0, 0, 1) || normals[i] == osg::Vec3d(0, 0, -1)) {
			colors->push_back(osg::Vec4(0.0f, 0.7f, 0.0f, 1.0f) ); //index 1 green
			colors->push_back(osg::Vec4(0.0f, 0.7f, 0.0f, 1.0f) ); //index 1 green
			colors->push_back(osg::Vec4(0.0f, 0.7f, 0.0f, 1.0f) ); //index 1 green
		}
		else {
			colors->push_back(osg::Vec4(0.0f, 0.4f, 0.0f, 1.0f) ); //index 1 green
			colors->push_back(osg::Vec4(0.0f, 0.4f, 0.0f, 1.0f) ); //index 1 green
			colors->push_back(osg::Vec4(0.0f, 0.4f, 0.0f, 1.0f) ); //index 1 green
		}
		
		colors->push_back(osg::Vec4(0.0, 0.0, 0.0, 1.0));
		colors->push_back(osg::Vec4(0.0, 0.0, 0.0, 1.0));
		colors->push_back(osg::Vec4(0.0, 0.0, 0.0, 1.0));
	}
	
    //The next step is to associate the array of colors with the geometry,
    //assign the color indices created above to the geometry and set the
    //binding mode to _PER_VERTEX.
	
    _geom->setColorArray(colors.get());
    _geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	
	osg::LineWidth* lineWidth = new osg::LineWidth();
	lineWidth->setWidth(5.0f);
	_geom->getOrCreateStateSet()->setAttributeAndModes(lineWidth, osg::StateAttribute::ON);
	
	this->_geode->addDrawable(_geom);
	
	/*******************************************************************************************/
	
//	osg::ref_ptr<osg::Vec3Array> cubeVertices = new osg::Vec3Array;
//    cubeVertices->push_back( osg::Vec3( 0,       0,        0) ); // bottom front left
//    cubeVertices->push_back( osg::Vec3(dim.x(), 0,        0) ); // bottom front right
//    cubeVertices->push_back( osg::Vec3(dim.x(), dim.y(), 0) ); // bottom back right
//    cubeVertices->push_back( osg::Vec3( 0,       dim.y(), 0) ); // bottom back left
//	
//	cubeVertices->push_back( osg::Vec3( 0,       0,       dim.z()) ); // top front left
//    cubeVertices->push_back( osg::Vec3( dim.x(), 0,       dim.z()) ); // top front right
//    cubeVertices->push_back( osg::Vec3( dim.x(), dim.y(), dim.z()) ); // top back right
//    cubeVertices->push_back( osg::Vec3( 0,       dim.y(), dim.z()) ); // top back left
//	
//	
//    _geom->setVertexArray( cubeVertices.get() );
//	
//	osg::ref_ptr<osg::DrawElementsUInt> cubeBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
//    cubeBase->push_back(3);
//    cubeBase->push_back(2);
//    cubeBase->push_back(1);
//    cubeBase->push_back(0);
//    _geom->addPrimitiveSet(cubeBase.get());
//	
//	osg::ref_ptr<osg::DrawElementsUInt> cubeTop = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
//	cubeTop->push_back(7);
//	cubeTop->push_back(6);
//	cubeTop->push_back(5);
//	cubeTop->push_back(4);
//	_geom->addPrimitiveSet(cubeTop.get());
//	
//	osg::ref_ptr<osg::DrawElementsUInt> cubeFront = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
//	cubeFront->push_back(4);
//	cubeFront->push_back(0);
//	cubeFront->push_back(1);
//	cubeFront->push_back(5);
//	_geom->addPrimitiveSet(cubeFront.get());
//	
//	osg::ref_ptr<osg::DrawElementsUInt> cubeBack = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
//	cubeBack->push_back(7);
//	cubeBack->push_back(3);
//	cubeBack->push_back(2);
//	cubeBack->push_back(6);
//	_geom->addPrimitiveSet(cubeBack.get());
//	
//	osg::ref_ptr<osg::DrawElementsUInt> cubeLeft = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
//	cubeLeft->push_back(7);
//	cubeLeft->push_back(3);
//	cubeLeft->push_back(0);
//	cubeLeft->push_back(4);
//	_geom->addPrimitiveSet(cubeLeft.get());
//	
//	osg::ref_ptr<osg::DrawElementsUInt> cubeRight = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
//	cubeRight->push_back(5);
//	cubeRight->push_back(1);
//	cubeRight->push_back(2);
//	cubeRight->push_back(6);
//	_geom->addPrimitiveSet(cubeRight.get());
//	
//    //Declare and load an array of Vec4 elements to store colors.
//	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();
//    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
//    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
//    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
//    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white
//    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f) ); //index 4 yellow
//	colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f) ); //index 5 purple
//	colors->push_back(osg::Vec4(1.0f, 0.5f, 0.5f, 1.0f) ); //index 6 something
//	colors->push_back(osg::Vec4(0.0f, 0.4f, 0.8f, 1.0f) ); //index 7 something else
//	
//    //The next step is to associate the array of colors with the geometry,
//    //assign the color indices created above to the geometry and set the
//    //binding mode to _PER_VERTEX.
//	
//    _geom->setColorArray(colors.get());
//    _geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
//	this->_geode->addDrawable(_geom);	
	/*******************************************************************************************/
}

Voxel::~Voxel() {
	
}
