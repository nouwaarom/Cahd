#ifndef GPGPU_H
#define GPGPU_H
//includes
#include <glib.h>
#include <glib/gstdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//defines

//global variables
//program handlers
GLuint rp, cp;
//shader handlers
GLuint cs, vs, fs;
//texture handlers
GLuint textureHandle;

//functions
void init();

GLuint setupRenderProgram();
GLuint setupComputeProgram();

GLuint generateTexture();
void generalPurposeCalculation(void);
void printLog(GLuint obj);

//glut callbacks
void display(void);
void keyboard(unsigned char key, int x, int y);

//exit
void freeStorage();

#endif
