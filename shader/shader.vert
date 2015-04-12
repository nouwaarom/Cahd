#version 430
 
void main()
{   
	//this is a magic line of code you need if you want to use textures         
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    // Set the position of the current vertex 
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
