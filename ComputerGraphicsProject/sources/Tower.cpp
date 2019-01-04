#include "../headers/Tower.h"

Tower::Tower()
{

}

Tower::Tower(glm::vec3 position, GeometryNode* g_node) {
	setPosition(position);
	m_geometric_node = g_node;
}

void Tower::setPosition(glm::vec3 position) {
	m_position = position;
	m_geometric_transformation_matrix =
		glm::translate(glm::mat4(1.f), getPosition()) *
		glm::scale(glm::mat4(1.f), glm::vec3(0.25f));
	m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
}

glm::vec3 Tower::getPosition() {
	return m_position;
}

GeometryNode* Tower::getGeometricNode() {
	return m_geometric_node;
}

glm::mat4 Tower::getGeometricTransformationMatrix()
{
	return m_geometric_transformation_matrix;
}

glm::mat4 Tower::getGeometricTransformationNormalMatrix()
{
	return m_geometric_transformation_normal_matrix;
}

Tower::~Tower()
{
}
