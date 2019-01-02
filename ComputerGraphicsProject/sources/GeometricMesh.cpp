#include "../headers/GeometricMesh.h"
#include "../headers/OBJLoader.h"
#include <sstream>

GeometricMesh::GeometricMesh()
{

}


OBJMaterial* GeometricMesh::findMaterial(std::string str)
{
	if (str.empty()) str = "default";
	for (unsigned int i = 0; i<materials.size(); i++)
	{
		if (materials[i].name == str) return &materials[i];
	}
	return NULL;
}

int GeometricMesh::findMaterialID(std::string str)
{
	if (str.empty()) str = "default";
	for (unsigned int i = 0; i<materials.size(); i++)
	{
		if (materials[i].name == str)
			return i;
	}
	return -1;
}

void GeometricMesh::printObjects(void)
{
	printf("\n          OBJECTS   :\n");
	printf("Vertices =%zu \nNormals =%zu \nTextureCoords=%zu\n", vertices.size(), normals.size(), textureCoord.size());
	printf("We loaded %zu meshes\n", objects.size());
	glm::vec3 minValue(FLT_MAX);
	glm::vec3 maxValue(-FLT_MAX);
	for (glm::vec3 vertex : vertices)
	{
		minValue = glm::min(minValue, vertex);
		maxValue = glm::max(minValue, vertex);
	}
	printf("Min %f %f %f", minValue.x, minValue.y, minValue.z);
	printf("Max %f %f %f", maxValue.x, maxValue.y, maxValue.z);
	for (unsigned int i = 0; i<objects.size(); i++)
	{
		printf("\nObject %d ", i);
		if (objects[i].name.size() > 0) printf("%s \n", objects[i].name.c_str());
		else printf("\n");
		printf("From %d to %d with %d faces\n", objects[i].start, objects[i].end, (objects[i].end - objects[i].start) / 3);
		if (objects[i].material_id > 0) printf("Uses %d : %s material\n", objects[i].material_id, materials[objects[i].material_id].name.c_str());
		else printf("Uses NO material\n");
	}

}
void GeometricMesh::printMaterials(void)
{
	if (materials.empty()) printf(" NO MATERIALS \n");
	else printf("\n USED MATERIALS :\n");
	for (unsigned int i = 0; i<materials.size(); i++)
	{
		printf("%i ", i);
		printf("Diffuse : %f %f %f\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
	}
}
