#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
		//define something for Windows (64-bit only)
		#include "../headers/GeometryNode.h"
		#include "../headers/GeometricMesh.h"
		#include <glm/gtc/type_ptr.hpp>
		#include "../headers/TextureManager.h"
	#endif
#elif __APPLE__
	// apple
	#include "TargetConditionals.h"
	#include "../headers/GeometryNode.h"
	#include "../headers/GeometricMesh.h"
	#include <../glm/gtc/type_ptr.hpp>
	#include "../headers/TextureManager.h"
    #include <iostream>
#elif __linux__
	// linux
	#include "../headers/GeometryNode.h"
	#include "../headers/GeometricMesh.h"
	#include <../glm/gtc/type_ptr.hpp>
	#include "../headers/TextureManager.h"
#endif

GeometryNode::GeometryNode()
{
	m_vao = 0;
	m_vbo_positions = 0;
	m_vbo_normals = 0;
	m_vbo_texcoords = 0;
	m_vbo_tangents = 0;
}

GeometryNode::~GeometryNode()
{
	// delete buffers
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo_positions);
	glDeleteBuffers(1, &m_vbo_normals);
	glDeleteBuffers(1, &m_vbo_texcoords);
	glDeleteBuffers(1, &m_vbo_tangents);
}

void GeometryNode::Init(GeometricMesh* mesh)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_positions);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_positions);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(glm::vec3), &mesh->vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,				// attribute index
		3,              // number of elements per vertex, here (x,y,z)
		GL_FLOAT,       // the type of each element
		GL_FALSE,       // take our values as-is
		0,		         // no extra data between each position
		0				// pointer to the C array or an offset to our buffer
	);

	glGenBuffers(1, &m_vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, mesh->normals.size() * sizeof(glm::vec3), &mesh->normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,				// attribute index
		3,              // number of elements per vertex, here (x,y,z)
		GL_FLOAT,		// the type of each element
		GL_FALSE,       // take our values as-is
		0,		         // no extra data between each position
		0				// pointer to the C array or an offset to our buffer
	);

	if (!mesh->textureCoord.empty())
	{
		glGenBuffers(1, &m_vbo_texcoords);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_texcoords);
		glBufferData(GL_ARRAY_BUFFER, mesh->textureCoord.size() * sizeof(glm::vec2), &mesh->textureCoord[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,				// attribute index
			2,              // number of elements per vertex, here (x,y,z)
			GL_FLOAT,		// the type of each element
			GL_FALSE,       // take our values as-is
			0,		         // no extra data between each position
			0				// pointer to the C array or an offset to our buffer
		);
	}

	if (!mesh->tangents.empty())
	{
		glGenBuffers(1, &m_vbo_tangents);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_tangents);
		glBufferData(GL_ARRAY_BUFFER, mesh->tangents.size() * sizeof(glm::vec3), &mesh->tangents[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(
			3,				// attribute index
			3,              // number of elements per vertex, here (x,y,z)
			GL_FLOAT,		// the type of each element
			GL_FALSE,       // take our values as-is
			0,		         // no extra data between each position
			0				// pointer to the C array or an offset to our buffer
		);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// *********************************************************************

	for (int i = 0; i < mesh->objects.size(); i++)
	{
		Objects part;
		part.start_offset = mesh->objects[i].start;
		part.count = mesh->objects[i].end - mesh->objects[i].start;
		auto material = mesh->materials[mesh->objects[i].material_id];

        part.diffuseColor = glm::vec4(material.diffuse[0], material.diffuse[1], material.diffuse[2], 1.0f);
		part.specularColor = glm::vec3(material.specular[0], material.specular[1], material.specular[2]);
		part.shininess = material.shininess;
		part.textureID = (material.texture.empty())? 0 : TextureManager::GetInstance().RequestTexture(material.texture.c_str());
		part.normalMapID = (material.textureBump.empty())? 0 : TextureManager::GetInstance().RequestTexture(material.textureBump.c_str());

		parts.push_back(part);
	}
}


