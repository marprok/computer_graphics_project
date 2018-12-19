#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

#include <vector>
#include "GLEW\glew.h"
#include <unordered_map>
#include "glm\gtx\hash.hpp"

class GeometryNode
{
public:
	GeometryNode();
	~GeometryNode();

	void Init(class GeometricMesh* mesh);

	struct Objects
	{
		unsigned int start_offset;
		unsigned int count;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;
		float shininess;
		GLuint textureID;
		GLuint normalMapID;
	};
	std::vector<Objects> parts;

	GLuint m_vao;
	GLuint m_vbo_positions;
	GLuint m_vbo_normals;
	GLuint m_vbo_texcoords;
	GLuint m_vbo_tangents;
};

#endif