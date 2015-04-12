#version 430

uniform image2D texture;
uniform vec2 connectedPoints[1024];

/* *** default input of compute shader ***
in uvec3 gl_NumWorkGroups;
in uvec3 gl_WorkGroupID;
in uvec3 gl_LocalInvocationID;
in uvec3 gl_GlobalInvocationID;
in uint  gl_LocalInvocationIndex;
*/

//compute shader input (work group size qualifiers)
layout (local_size_x = 16, local_size_y = 16) in;

void main()
{
	ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
	float localCoef = length(vec2(ivec2(gl_LocalInvocationID.xy)-8)/8.0);
	float globalCoef = sin(float(gl_WorkGroupID.x+gl_WorkGroupID.y)*0.1 + 0.02)*0.5;
	imageStore(texture, storePos, vec4(0.6-globalCoef*localCoef, 0.9, 0.2, 0.0));
}
