#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
		//define something for Windows (64-bit only)
		#include <vector>
		#include "GLEW/glew.h"
		#include "OBJLoader.h"
		#include <string>
	#endif
#elif __APPLE__
	// apple
	#include "TargetConditionals.h"
	#include <vector>
	#include "../GLEW/glew.h"
	#include <unordered_map>
	#include "../glm/gtx/hash.hpp"
#elif __linux__
	// linux
	#include <vector>
	#include "../GLEW/glew.h"
	#include <unordered_map>
	#include "../glm/gtx/hash.hpp"
#endif

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
        bool gs=false;
		float shininess;
		GLuint textureID;
		GLuint normalMapID;
	};
	std::vector<Objects> parts;
	
	float alpha;

	GLuint m_vao;
	GLuint m_vbo_positions;
	GLuint m_vbo_normals;
	GLuint m_vbo_texcoords;
	GLuint m_vbo_tangents;
};

#endif
