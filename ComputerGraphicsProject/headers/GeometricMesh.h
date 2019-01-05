#ifndef GEOMETRIC_MESH_H
#define GEOMETRIC_MESH_H

#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
		//define something for Windows (64-bit only)
		#include <vector>
		#include <glm/glm.hpp>
		#include "OBJLoader.h"
		#include <string>
	#endif
#elif __APPLE__
	// apple
	#include "TargetConditionals.h"
	#include <vector>
	#include <../glm/glm.hpp>
	#include "OBJLoader.h"
	#include <string>
#elif __linux__
	// linux
	#include <vector>
	#include <../glm/glm.hpp>
	#include "OBJLoader.h"
	#include <string>
#endif

class GeometricMesh
{
public:
	GeometricMesh();

	struct OBJMaterial* findMaterial(std::string str);
	int findMaterialID(std::string str);

	/// test functions
	void printObjects(void);
	void printMaterials(void);

	// variables
	struct MeshObject
	{
		int material_id;
		unsigned int start;
		unsigned int end;
		std::string name;
	};
	std::vector<MeshObject> objects;
	std::vector<OBJMaterial> materials;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoord;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
};

#endif