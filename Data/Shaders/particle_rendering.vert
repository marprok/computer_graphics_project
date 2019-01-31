#version 330 core
layout(location = 0) in vec3 coord3d;

uniform mat4 uniform_view_matrix;
uniform mat4 uniform_projection_matrix;

void main(void) 
{
	gl_PointSize = 2;
	gl_Position = uniform_projection_matrix * uniform_view_matrix * vec4(coord3d, 1.0);
}
