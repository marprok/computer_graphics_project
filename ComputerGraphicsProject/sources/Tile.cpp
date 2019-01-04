#include "../headers/Tile.h"

Tile::Tile()
{
}

Tile::Tile(int width, int height, glm::vec3 position, GeometryNode* g_node) {
	setPosition(position);
	m_geometric_node = g_node;
}

void Tile::setPosition(glm::vec3 position) {
	m_position = position;
	m_position.x *= 2;
	m_position.z *= 2;
	m_geometric_transformation_matrix =
		glm::translate(glm::mat4(1.f), glm::vec3(getPosition().x, getPosition().y, getPosition().z));
	m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
}

glm::vec3 Tile::getPosition() {
	return m_position;
}

GeometryNode* Tile::getGeometricNode() {
	return m_geometric_node;
}

glm::mat4 Tile::getGeometricTransformationMatrix()
{
	return m_geometric_transformation_matrix;
}

glm::mat4 Tile::getGeometricTransformationNormalMatrix()
{
	return m_geometric_transformation_normal_matrix;
}

Tile::~Tile()
{
}
