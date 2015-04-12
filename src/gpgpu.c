#include "gpgpu.h"

void init(int argc, char **argv)
{
	/* Initialize glut*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("test");

	/* Initialize openGL*/
	glPolygonMode(GL_FRONT, GL_POINT);

	printf("OpenGL:\n\tvendor %s\n\trenderer %s\n\tversion %s\n\tshader language %s\n",
		    glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));
}

/* Compile and link the rendering program */
GLuint setupRenderProgram()
{
 	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	GLchar *vsSource, *fsSource;
	g_file_get_contents("Shader/shader.vert", &vsSource, NULL, NULL);
	g_file_get_contents("Shader/shader.frag", &fsSource, NULL, NULL);
	glShaderSource(vs, 1, &vsSource, NULL);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
	glCompileShader(vs);
	printLog(vs);
	printLog(fs);
 	rp = glCreateProgram();
	glAttachShader(rp, vs);
	glAttachShader(rp, fs);
	glLinkProgram(rp);
	printLog(rp);

	//store handles
	textureHandle = generateTexture();
	glUniform1i(glGetUniformLocation(rp, "texture"), GL_TEXTURE0);

	//free source buffers
	free(vsSource);
	free(fsSource);
}

/* Compile and link the computing program */
GLuint setupComputeProgram()
{
	cs = glCreateShader(GL_COMPUTE_SHADER);
	GLchar *csSource;
	g_file_get_contents("Shader/gpgpu.comp", &csSource, NULL, NULL);
	glShaderSource(cs, 1, &csSource, NULL);
	glCompileShader(cs);
	printLog(cs);
	cp = glCreateProgram();
	glAttachShader(cp, cs);
 	glLinkProgram(cp);
 	printLog(cp);

 	//store handles
 	glUniform1i(glGetUniformLocation(cp, "texture"), GL_TEXTURE0);

 	//free source buffers
 	free(csSource);
}

// We create a single float channel 512^2 texture
GLuint generateTexture()
{
	GLuint texHandle;
	glGenTextures(1, &texHandle);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texHandle);

	//set the parameters for the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 512, 512, 0, GL_RGB, GL_FLOAT, NULL);

	// Because we're also using this tex as an image (in order to write to it),
	// we bind it to an image unit as well
	glBindImageTexture(0, texHandle, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	return texHandle;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(rp);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glDisable(GL_LIGHTING);

	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(10, 10, 0);
	glTexCoord2f(0, 1); glVertex3f(10, glutGet(GLUT_WINDOW_HEIGHT)-10, 0);
	glTexCoord2f(1, 1); glVertex3f(glutGet(GLUT_WINDOW_WIDTH)-10, glutGet(GLUT_WINDOW_HEIGHT)-10, 0);
	glTexCoord2f(1, 0); glVertex3f(glutGet(GLUT_WINDOW_WIDTH)-10, 10, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'g':
			generalPurposeCalculation();
			break;

		case 'a':
			break;
		case 'd':
			break;

		case 'w':
			break;
		case 's':
			break;
	}
	display();
}

void printLog(GLuint obj)
{
    int infologLength = 0;
    char infoLog[1024];

	if (glIsShader(obj))
		glGetShaderInfoLog(obj, 1024, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, 1024, &infologLength, infoLog);

    if (infologLength > 0)
		printf("%s\n", infoLog);
}

void generalPurposeCalculation(void)
{
	printf("computing on gpu ...\n");
	glUseProgram(cp);
	glDispatchCompute(512/16, 512/16, 1); // 512^2 threads in blocks of 16^2
	//convert gates to transistors

	//placement


	//global routing

	//local routing
}

void freeStorage()
{
	//cleanup before returning
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(cs);
	glDeleteProgram(rp);
	glDeleteProgram(cp);
}
