#include "../headers/Skeleton.h"

#define PI 3.14159f

Skeleton::Skeleton()
{
}

Skeleton::Skeleton(glm::vec3 position, int goal, float hand_start_rotation, std::vector<Tile> &road, GeometryNode ** g_node, int health)
{
    setPosition(position, 0, 0);
    setGoal(goal);
    m_road = road;
    m_rotation = 3.14f;
    m_velocity = 2.f;
    m_geometric_node = g_node;
	m_hand_start_rotation = hand_start_rotation;
    m_health = health;
}

void Skeleton::setPosition(glm::vec3 position, float angle, float continuous_time) {
    m_position = position;
	m_rotation = angle;
    m_position.y = 0.1f;

	glm::mat4 pirate_position;
	pirate_position =
		glm::translate(glm::mat4(1.0f), m_position) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.11, 0)) *
		glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 1, 0)) *
		glm::scale(glm::mat4(1.0), glm::vec3(0.09f));

    // body
    //m_geometric_transformation_matrix[0] = glm::rotate(m_geometric_transformation_matrix[0], m_rotation, glm::vec3(0, 1, 0));
	m_geometric_transformation_matrix[0] =
		pirate_position;
        //glm::rotate(glm::mat4(1.0), m_rotation, glm::vec3(0, 1, 0));
    m_geometric_transformation_normal_matrix[0] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[0]))));

    // arm
    //m_geometric_transformation_matrix[1] = glm::rotate(m_geometric_transformation_matrix[1], m_rotation, glm::vec3(0, 1, 0));
    //0.45f, 1.f, -0.2f
	m_geometric_transformation_matrix[1] =
		pirate_position *
		glm::translate(glm::mat4(1.0), glm::vec3(4.5f, 12.f, 0.f)) *
		glm::rotate(glm::mat4(1.0), 0.8f * std::sin(2 * m_velocity * continuous_time), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), m_hand_start_rotation, glm::vec3(1, 0, 0)) *
		glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -3.f));

    m_geometric_transformation_normal_matrix[1] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[1]))));


    // right foot
    //m_geometric_transformation_matrix[2] = glm::rotate(m_geometric_transformation_matrix[2], m_rotation , glm::vec3(0, 1, 0));
    //-0.3f, 0.f, -0.2f
    m_geometric_transformation_matrix[2] =
		pirate_position *
        glm::translate(glm::mat4(1.0), glm::vec3(-4.f, 0.f, -2.f * std::sin(continuous_time * 4 * m_velocity)));

    m_geometric_transformation_normal_matrix[2] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[2]))));

    // left foot
    //m_geometric_transformation_matrix[3] = glm::rotate(m_geometric_transformation_matrix[3], m_rotation, glm::vec3(0, 1, 0));
    //+0.3f, 0.f, -0.2f
    m_geometric_transformation_matrix[3] =
		pirate_position *
        glm::translate(glm::mat4(1.0), glm::vec3(4.f, 0.f, 2.f * std::sin(continuous_time * 4 * m_velocity)));
    m_geometric_transformation_normal_matrix[3] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[3]))));

}

void Skeleton::setGoal(int goal)
{
    m_goal = goal;
}

void Skeleton::Move(float dt, float continuous_time)
{
    float rotation;
    glm::vec3 delta_skeleton = m_road[m_goal].getPosition() - m_position;

    if (std::abs(delta_skeleton.z) < 0.2f && std::abs(delta_skeleton.x) < 0.2f && m_goal < m_road.size() - 1)
    {
        if (!(m_goal + 1 == m_road.size()))
        {
            setGoal(m_goal + 1);
			delta_skeleton = m_road[m_goal].getPosition() - m_position;
        }
        else
        {
            std::cout << "Treasure reached!" << std::endl;
        }
    }

	float angle = 0.f;
    //delta_skeleton *= dt * m_velocity;
    if(delta_skeleton.x > 0 && std::abs(delta_skeleton.x) > std::abs(delta_skeleton.z))
    {
        m_position.x += dt*m_velocity;
		angle = 3 * PI / 2;
        //std::cout << "x>0" <<std::endl;

    }else if (delta_skeleton.x < 0 && std::abs(delta_skeleton.z) < std::abs(delta_skeleton.x))
    {
        m_position.x -= dt*m_velocity;
		angle = PI / 2;
        //std::cout << "x<0" <<std::endl;

    }else if(delta_skeleton.z > 0 && std::abs(delta_skeleton.z) > std::abs(delta_skeleton.x))
    {
        //std::cout << "z>0" <<std::endl;
        m_position.z += dt*m_velocity;
		angle = PI;

    }else if (delta_skeleton.z < 0 && std::abs(delta_skeleton.z) > std::abs(delta_skeleton.x))
    {
        //std::cout << "z<0 "<<std::endl;
        m_position.z -= dt*m_velocity;

    }

    setPosition(m_position, angle, continuous_time);
}

glm::vec3 Skeleton::getPosition() {
    return m_position;
}

GeometryNode** Skeleton::getGeometricNode() {
    return m_geometric_node;
}

void Skeleton::setVelocity(float new_velocity)
{
    m_velocity = new_velocity;
}

float Skeleton::getVelocity()
{
    return m_velocity;
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

float Skeleton::distance_from(int x, int z)
{
    float distance = std::sqrt((m_position.x - x)*(m_position.x - x) + (m_position.z - z)*(m_position.z - z));
    return (distance <= 1.0f)? distance : -1.0f;
}

void Skeleton::lose_health(int i)
{
    m_health = (m_health - i < 0) ? 0 : m_health - i;
    std::cout << "health = " << m_health << std::endl;
}

int Skeleton::get_health()
{
    return m_health;
}
