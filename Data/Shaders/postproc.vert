#version 330 core
layout(location = 0) in vec2 coord2d;

out vec2 f_texcoord;

void main(void)
{
	gl_Position = vec4(coord2d, 0.0, 1.0);
	f_texcoord = (coord2d + 1.0) / 2.0;
}