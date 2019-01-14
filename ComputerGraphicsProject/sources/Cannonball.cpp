#include "../headers/Cannonball.h"
#include <map>

Cannonball::Cannonball()
{

}

Cannonball::Cannonball(glm::vec3 position, GeometryNode* g_node, int target, float speed) {
    m_geometric_node = g_node;
    position.y = 2.5f;
    setPosition(position);
    m_target = target;
    m_speed = speed;
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
    glm::vec3 delta_cannonball = skeletons[m_target].getPosition() - m_position;


    if(delta_cannonball.x > 0 && std::abs(delta_cannonball.x) > std::abs(delta_cannonball.z))
    {
        m_position.x += dt*m_speed;
        //std::cout << "x>0" <<std::endl;

    }
    if (delta_cannonball.x < 0 && std::abs(delta_cannonball.z) < std::abs(delta_cannonball.x))
    {
        m_position.x -= dt*m_speed;
        //std::cout << "x<0" <<std::endl;

    }
    if(delta_cannonball.z > 0 && std::abs(delta_cannonball.z) > std::abs(delta_cannonball.x))
    {
        //std::cout << "z>0" <<std::endl;
        m_position.z += dt*m_speed;

    }
    if (delta_cannonball.z < 0 && std::abs(delta_cannonball.z) > std::abs(delta_cannonball.x))
    {
        //std::cout << "z<0 "<<std::endl;
        m_position.z -= dt*m_speed;
    }

    m_position.y -= gravity *dt;
    if(m_position.y < 0 )
    {
        return false;
    }


    setPosition(m_position);

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


