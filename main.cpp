//
//  main.cpp
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/20/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#include "main.hpp"
#include "Voxel.h"

int main()
{
	//osg::setNotifyLevel(osg::NotifySeverity::DEBUG_INFO);
	
    osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<Voxel> cube = new Voxel();
	
			
	root->addChild(cube.get());
	
	// Let's build a hollow cube! :D
		
//	for(int x = 0; x < 32; x++) {
//		for(int y = 0; y < 32; y++) {
//			for(int z = 0; z < 32; z++) {
//				if(x == 0 || y == 0 || z == 0 || x == 31 || y == 31 || z == 31) {
//					osg::ref_ptr<osg::PositionAttitudeTransform> cubeTwoXForm = new osg::PositionAttitudeTransform();
//					cubeTwoXForm->setPosition( osg::Vec3d(x, y, z) );
//					root->addChild(cubeTwoXForm.get());
//					cubeTwoXForm->addChild(cube);
//				}
//			}
//		}
//	}
	
	int r = 5;
	
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			double z = sqrt(r*r - y*y - x*x);
			// top quadrant 1
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormTopQuad1 = new osg::PositionAttitudeTransform();
			cubeXFormTopQuad1->setPosition( osg::Vec3d(x, y, z) );
			root->addChild(cubeXFormTopQuad1.get());
			cubeXFormTopQuad1->addChild(cube);
			
			// top quadrant 2
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormTopQuad2 = new osg::PositionAttitudeTransform();
			cubeXFormTopQuad2->setPosition( osg::Vec3d(-x, y, z) );
			root->addChild(cubeXFormTopQuad2.get());
			cubeXFormTopQuad2->addChild(cube);
			
			// top quadrant 3
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormTopQuad3 = new osg::PositionAttitudeTransform();
			cubeXFormTopQuad3->setPosition( osg::Vec3d(-x, -y, z) );
			root->addChild(cubeXFormTopQuad3.get());
			cubeXFormTopQuad3->addChild(cube);
			
			// top quadrant 4
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormTopQuad4 = new osg::PositionAttitudeTransform();
			cubeXFormTopQuad4->setPosition( osg::Vec3d(x, -y, z) );
			root->addChild(cubeXFormTopQuad4.get());
			cubeXFormTopQuad4->addChild(cube);
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			// bottom quadrant 1
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormBottomQuad1 = new osg::PositionAttitudeTransform();
			cubeXFormBottomQuad1->setPosition( osg::Vec3d(x, y, -z) );
			root->addChild(cubeXFormBottomQuad1.get());
			cubeXFormBottomQuad1->addChild(cube);
			
			// bottom quadrant 2
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormBottomQuad2 = new osg::PositionAttitudeTransform();
			cubeXFormBottomQuad2->setPosition( osg::Vec3d(-x, y, -z) );
			root->addChild(cubeXFormBottomQuad2.get());
			cubeXFormBottomQuad2->addChild(cube);
			
			// bottom quadrant 3
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormBottomQuad3 = new osg::PositionAttitudeTransform();
			cubeXFormBottomQuad3->setPosition( osg::Vec3d(-x, -y, -z) );
			root->addChild(cubeXFormBottomQuad3.get());
			cubeXFormBottomQuad3->addChild(cube);
			
			// bottom quadrant 4
			osg::ref_ptr<osg::PositionAttitudeTransform> cubeXFormBottomQuad4 = new osg::PositionAttitudeTransform();
			cubeXFormBottomQuad4->setPosition( osg::Vec3d(x, -y, -z) );
			root->addChild(cubeXFormBottomQuad4.get());
			cubeXFormBottomQuad4->addChild(cube);


		}
	}
	

    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	
	
    viewer.setSceneData( root.get() );
    //viewer.run();
	
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.realize();
		
    while( !viewer.done() )
    {
        viewer.frame();
    }
	
    return 0;
}
