#include <stdio.h>
#include "gpgpu.h"

int start(int argc, char **argv)
{
	//init openGL
	init(argc, argv);

	//generate texture
 	textureHandle = generateTexture();

	//setup gpu programs
	setupRenderProgram();
	setupComputeProgram();

 	//setup callbacks
 	glutDisplayFunc(display);
 	glutKeyboardFunc(keyboard);

 	//start the program
 	glutMainLoop();

 	freeStorage();

	return(1);
}
