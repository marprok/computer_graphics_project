#pragma once
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GeometryNode.h"

class Tower
{
public:
	Tower();
	Tower(glm::vec3 position, GeometryNode* g_node);
	~Tower();

	void setPosition(glm::vec3 position);

	glm::vec3 getPosition();

	GeometryNode* getGeometricNode();

	glm::mat4 getGeometricTransformationMatrix();

	glm::mat4 getGeometricTransformationNormalMatrix();

private:
	glm::vec3				m_position;
	glm::mat4				m_geometric_transformation_matrix;
	glm::mat4				m_geometric_transformation_normal_matrix;

	GeometryNode*			m_geometric_node;
};
