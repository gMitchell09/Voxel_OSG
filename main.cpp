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
#include <noise/noise.h>
#include <noiseutils.h>

int main()
{
	//osg::setNotifyLevel(osg::NotifySeverity::DEBUG_INFO);
    osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group();
	
	std::vector<osg::ref_ptr<osg::Node>> nodeVector;
	
//	// Let's build a hollow cube! :D
//		
//	for(int x = 0; x < 32; x++) {
//		for(int y = 0; y < 32; y++) {
//			for(int z = 0; z < 32; z++) {
//				if(x == 0 || y == 0 || z == 0 || x == 31 || y == 31 || z == 31) {
//					
//					osg::ref_ptr<Voxel> cube = new Voxel(osg::Vec3d(1, 1, 1), osg::Vec3d(x, y, z), 127);
//					nodeVector.push_back(cube);
//					
//				}
//			}
//		}
//	}

	noise::module::Perlin noiseModule;
	noiseModule.SetFrequency(1.0);
	noiseModule.SetOctaveCount(2);
	
	// Let's Build a terrain
	
	for(int x = 0; x < 128; x++) {
		for(int y = 0; y < 128; y++) {
			for(int z = 0; z <= abs(2*noiseModule.GetValue(1.5*x, 1.5*y, 1.5)); z++) {
				double val = noiseModule.GetValue(1.5*x, 1.5*y, 1.5*z);
				int cornerVals = 0;
				
				if(val < 0.0) {
					cornerVals |= 1 | 2 | 4 | 8;
				}
				else {
					
					/* 8 corners:
					 x-1, y+1, z-1
					 x+1, y+1, z-1
					 x+1, y-1, z-1
					 x-1, y-1, z-1
					 
					 x-1, y+1, z+1
					 x+1, y+1, z+1
					 x+1, y-1, z+1
					 x-1, y-1, z+1

					*/
//					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y+1), 1.5*(z-1))) cornerVals |= 1;
//					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y+1), 1.5*(z-1))) cornerVals |= 2;
//					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y-1), 1.5*(z-1))) cornerVals |= 4;
//					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y-1), 1.5*(z-1))) cornerVals |= 8;
//					
//					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y+1), 1.5*(z+1))) cornerVals |= 16;
//					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y+1), 1.5*(z+1))) cornerVals |= 32;
//					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y-1), 1.5*(z+1))) cornerVals |= 64;
//					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y-1), 1.5*(z+1))) cornerVals |= 128;
					
					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y+1), 1.5*(z))) cornerVals |= 1; else cornerVals |= 16;
					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y+1), 1.5*(z))) cornerVals |= 2; else cornerVals |= 32;
					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y-1), 1.5*(z))) cornerVals |= 4; else cornerVals |= 64;
					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y-1), 1.5*(z))) cornerVals |= 8; else cornerVals |= 128;
					
					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y+1), 1.5*(z-1))) cornerVals |= 1;
					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y+1), 1.5*(z-1))) cornerVals |= 2;
					if (val >= noiseModule.GetValue(1.5*(x+1), 1.5*(y-1), 1.5*(z-1))) cornerVals |= 4;
					if (val >= noiseModule.GetValue(1.5*(x-1), 1.5*(y-1), 1.5*(z-1))) cornerVals |= 8;

				}
				osg::ref_ptr<Voxel> cube = new Voxel(osg::Vec3d(1, 1, 1), osg::Vec3d(x, y, z), cornerVals);
				nodeVector.push_back(cube);

				std::cout << "Noise Val: " << val << std::endl;
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
