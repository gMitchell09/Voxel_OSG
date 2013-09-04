//
//  main.cpp
//  Voxel_Render
//
//  Created by Mitchell, George  AMRDEC/Simtech on 8/20/13.
//  Copyright (c) 2013 Mitchell, George  AMRDEC/Simtech. All rights reserved.
//

#include "main.hpp"
#include "Voxel.h"
#include "Chunk.h"

int main()
{
	//osg::setNotifyLevel(osg::NotifySeverity::DEBUG_INFO);
    osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group();
	
	std::vector<osg::ref_ptr<osg::Node>> nodeVector;
	
	// Let's build a hollow cube! :D
		
	for(int x = 0; x < 32; x++) {
		for(int y = 0; y < 32; y++) {
			for(int z = 0; z < 32; z++) {
				if(x == 0 || y == 0 || z == 0 || x == 31 || y == 31 || z == 31) {
					
					osg::ref_ptr<Voxel> cube = new Voxel(osg::Vec3d(1, 1, 1), osg::Vec3d(x, y, z), 127);
					nodeVector.push_back(cube);
					
				}
			}
		}
	}
	
	osg::ref_ptr<Chunk> chunk = new Chunk(nodeVector);
	
	root->addChild(chunk);

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
