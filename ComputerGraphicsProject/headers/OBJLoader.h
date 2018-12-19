#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <unordered_map>
#include <future>
#include "GeometricMesh.h"

struct OBJMaterial
{
	std::string name;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float alpha;
	float shininess;
	int illumination_model;

	//texures
	std::string texture;
	std::string textureSpecular;
	std::string textureAmbient;
	std::string textureBump;
	std::string textureSpecularity;
	std::string textureOpacity;

	//constructor
	OBJMaterial()
	{ 
		ambient[0] = 0.2f;
		ambient[1] = 0.2f;
		ambient[2] = 0.2f;
		ambient[3] = 1.0f;

		diffuse[0] = 0.8f;
		diffuse[1] = 0.8f;
		diffuse[2] = 0.8f;
		diffuse[3] = 1.0f;

		specular[0] = 0.0f;
		specular[1] = 0.0f;
		specular[2] = 0.0f;
		specular[3] = 1.0f;

		alpha = 1;
		shininess = 0;
		illumination_model = 0;
	}
};

/* Loader for the Obj Format
It supports triangles and quads (it breaks them into two triangles)
It supports negative indices in the faces
If there are no normals it creates them
Returns a Mesh object for the GPU Rendering or a List of Triangles for Path Tracing
-- Thread safe and possible the new version
*/
class OBJLoader
{
	//shared vertices / textureCoord / normals 
	std::vector<glm::vec3> shared_vertices;
	std::vector<glm::vec3> shared_normals;
	std::vector<glm::vec2> shared_textcoord;
	struct Face
	{
		glm::ivec3 vertices;
		glm::ivec3 normals;
		glm::ivec3 texcoords;
	};
	std::vector<Face> shared_faces;

	// the element for calculating normals if they don't exists
	std::vector<unsigned int> elements;
	bool hasTextures;
	bool hasNormals;

	std::string folderPath;

	class GeometricMesh* mesh;

public:
	OBJLoader(void);
	~OBJLoader(void);

	class GeometricMesh * load(const char* filename);

private:
	void read_vertex(const char* buff);
	void read_texcoord(const char* buff);
	void read_normal(const char* buff);
	void read_face(const char* buff);
	void read_faceLimited(const char* buff);
	glm::ivec3 read_face_component(const char* buff, int& offset);
	void read_usemtl(const char* buff, int& currentMaterialID);
	void read_mtllib(const char* buff, const char* filename);
	void add_new_group(const char* buff, int& currentMaterialID);
	void parseMTL(const char* filename);

	void generateDataFromFaces();

	void calculate_flat_normals();
	void calculate_avg_normals(std::vector<glm::vec3> &shared_vertices, std::vector<glm::vec3> &normals, std::vector<unsigned int> &elements);

	void calculate_tangents();
};

