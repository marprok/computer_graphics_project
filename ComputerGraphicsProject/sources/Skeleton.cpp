#include "../headers/Skeleton.h"

Skeleton::Skeleton()
{
}

Skeleton::Skeleton(glm::vec3 position, int goal, std::vector<Tile> &road, GeometryNode ** g_node)
{
	setPosition(position);
	setGoal(goal);
	m_road = road;
	m_geometric_node = g_node;
}

void Skeleton::setPosition(glm::vec3 position) {
	m_position = position;
	m_position.y = 0.1f;

	// body
	m_geometric_transformation_matrix[0] =
		glm::translate(glm::mat4(1.0), m_position) *
		glm::scale(glm::mat4(1.0), glm::vec3(0.1f));
	m_geometric_transformation_normal_matrix[0] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[0]))));

	// arm
	m_geometric_transformation_matrix[1] =
		glm::translate(glm::mat4(1.0), glm::vec3(0.45f, 1.f, -0.2f) + m_position) *
		glm::scale(glm::mat4(1.0), glm::vec3(0.1f));
	m_geometric_transformation_normal_matrix[1] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[1]))));

	// right foot
	m_geometric_transformation_matrix[2] =
		glm::translate(glm::mat4(1.0), glm::vec3(-0.3f, 0.f, -0.2f) + m_position) *
		glm::scale(glm::mat4(1.0), glm::vec3(0.1f));
	m_geometric_transformation_normal_matrix[2] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[2]))));

	// left foot
	m_geometric_transformation_matrix[3] =
		glm::translate(glm::mat4(1.0), glm::vec3(0.3f, 0.f, -0.2f) + m_position) *
		glm::scale(glm::mat4(1.0), glm::vec3(0.1f));
	m_geometric_transformation_normal_matrix[3] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[3]))));
}

void Skeleton::setGoal(int goal)
{
	m_goal = goal;
}

void Skeleton::Move(float dt)
{
	glm::vec3 delta_skeleton = m_road[m_goal].getPosition() - m_position;
	
	if ((abs(delta_skeleton.x) < .3f && abs(delta_skeleton.z) < .3f) && m_goal < m_road.size() - 1)
	{
		std::cout << "Goal changed" << std::endl;
		if (!(m_goal + 1 == m_road.size()))
		{
			setGoal(m_goal + 1);
		}
		else
		{
			std::cout << "Treasure reached!" << std::endl;
		}
	}

	delta_skeleton *= dt * 3.f;

	setPosition(delta_skeleton + m_position);
}

glm::vec3 Skeleton::getPosition() {
	return m_position;
}

GeometryNode** Skeleton::getGeometricNode() {
	return m_geometric_node;
}

glm::mat4* Skeleton::getGeometricTransformationMatrix()
{
	return m_geometric_transformation_matrix;
}

glm::mat4* Skeleton::getGeometricTransformationNormalMatrix()
{
	return m_geometric_transformation_normal_matrix;
}

int Skeleton::GetGoal()
{
	return m_goal;
}

Skeleton::~Skeleton()
{
}
