#include "../headers/Cannonball.h"
#include <map>

Cannonball::Cannonball()
{

}

Cannonball::Cannonball(glm::vec3 position, GeometryNode* g_node, int target, float speed, glm::vec3 goal) {
    m_geometric_node = g_node;
    position.y = 2.5f;
    setPosition(position);
    m_radius = 0.2f;
    m_target = target;
    m_center_of_sphere = m_position;
    m_speed = speed;
	m_goal = goal;
	m_direction = m_goal - m_position;
}

void Cannonball::setPosition(glm::vec3 position) {
    m_position = position;
    m_geometric_transformation_matrix =
        glm::translate(glm::mat4(1.f), getPosition()) *
        glm::scale(glm::mat4(1.f), glm::vec3(0.2f));
    m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
}

bool Cannonball::update(float dt, std::vector<Skeleton> &skeletons, float gravity)
{

    if (skeletons.size() <= m_target)
    {
        return false;
    }

    //glm::vec3 delta_cannonball = skeletons[m_target].getPosition() - m_position;
    //glm::vec3 delta_cannonball = m_goal - m_position;
	glm::vec3 delta_cannonball = m_direction;
	std::cout << "goal: " << delta_cannonball.x << " " << delta_cannonball.y << " " << delta_cannonball.z << std::endl;

	if (delta_cannonball.x > 0)
	{
		m_position.x += dt * m_speed;
		std::cout << "x>0" << std::endl;

	}
	if (delta_cannonball.x < 0)
	{
		m_position.x -= dt * m_speed;
		std::cout << "x<0" << std::endl;

	}
	if (delta_cannonball.z > 0)
	{
		std::cout << "z>0" << std::endl;
		m_position.z += dt * m_speed;

	}
	if (delta_cannonball.z < 0)
	{
		std::cout << "z<0 " << std::endl;
		m_position.z -= dt * m_speed;
	}

    /*if(delta_cannonball.x > 0 && std::abs(delta_cannonball.x) > std::abs(delta_cannonball.z))
    {
        m_position.x += dt*m_speed;
        std::cout << "x>0" <<std::endl;

    }
    if (delta_cannonball.x < 0 && std::abs(delta_cannonball.z) < std::abs(delta_cannonball.x))
    {
        m_position.x -= dt*m_speed;
        std::cout << "x<0" <<std::endl;

    }
    if(delta_cannonball.z > 0 && std::abs(delta_cannonball.z) > std::abs(delta_cannonball.x))
    {
        std::cout << "z>0" <<std::endl;
        m_position.z += dt*m_speed;

    }
    if (delta_cannonball.z < 0 && std::abs(delta_cannonball.z) > std::abs(delta_cannonball.x))
    {
        std::cout << "z<0 "<<std::endl;
        m_position.z -= dt*m_speed;
    }*/

    m_position.y -= gravity *dt;
    if(m_position.y < 0)
    {
        return false;
    }
    setPosition(m_position);
    m_center_of_sphere = m_position;

    /*float distance = skeletons[m_target].distance_from(m_center_of_sphere);
    if(distance <= (m_radius + skeletons[m_target].getRadius()))
    {
        skeletons[m_target].lose_health(1);
        return false;
    }*/
	
	for (auto &skeleton : skeletons)
	{
		float distance = skeleton.distance_from(m_center_of_sphere);
		if (distance <= (m_radius + skeleton.getRadius()))
		{
			skeleton.lose_health(1);
			return false;
		}
	}
    return true;

}

glm::vec3 Cannonball::getPosition() {
    return m_position;
}

GeometryNode* Cannonball::getGeometricNode() {
    return m_geometric_node;
}

glm::mat4 Cannonball::getGeometricTransformationMatrix()
{
    return m_geometric_transformation_matrix;
}

glm::mat4 Cannonball::getGeometricTransformationNormalMatrix()
{
    return m_geometric_transformation_normal_matrix;
}

Cannonball::~Cannonball()
{
}


