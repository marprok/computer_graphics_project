#include "../headers/Skeleton.h"

Skeleton::Skeleton()
{
}

Skeleton::Skeleton(glm::vec3 position, int goal, std::vector<Tile> &road, GeometryNode ** g_node)
{
    setPosition(position, 0);
    setGoal(goal);
    m_road = road;
    m_rotation = 3.14f;
    m_velocity = 1.f;
    m_geometric_node = g_node;
}

void Skeleton::setPosition(glm::vec3 position, float a) {
    m_position = position;
    m_position.y = 0.1f;

    // body
    //m_geometric_transformation_matrix[0] = glm::rotate(m_geometric_transformation_matrix[0], m_rotation, glm::vec3(0, 1, 0));
    m_geometric_transformation_matrix[0] =
        glm::translate(glm::mat4(1.0), m_position) *
        glm::scale(glm::mat4(1.0), glm::vec3(0.1f))*
        glm::rotate(glm::mat4(1.0), m_rotation, glm::vec3(0, 1, 0));
    m_geometric_transformation_normal_matrix[0] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[0]))));


    // arm
    //m_geometric_transformation_matrix[1] = glm::rotate(m_geometric_transformation_matrix[1], m_rotation, glm::vec3(0, 1, 0));
    //0.45f, 1.f, -0.2f
    m_geometric_transformation_matrix[1] =
        glm::translate(glm::mat4(1.0), glm::vec3(-0.45f, 1.f, +0.2f) + m_position) *
        glm::scale(glm::mat4(1.0), glm::vec3(0.1f))*
        glm::rotate(glm::mat4(1.0), m_rotation, glm::vec3(0, 1, 0));

    m_geometric_transformation_normal_matrix[1] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[1]))));


    // right foot
    //m_geometric_transformation_matrix[2] = glm::rotate(m_geometric_transformation_matrix[2], m_rotation , glm::vec3(0, 1, 0));
    //-0.3f, 0.f, -0.2f
    m_geometric_transformation_matrix[2] =
        glm::translate(glm::mat4(1.0), glm::vec3(0.3f, 0.f, +0.2f) + m_position) *
        glm::scale(glm::mat4(1.0), glm::vec3(0.1f))*
        glm::rotate(glm::mat4(1.0), m_rotation, glm::vec3(0, 1, 0));

    m_geometric_transformation_normal_matrix[2] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[2]))));


    // left foot
    //m_geometric_transformation_matrix[3] = glm::rotate(m_geometric_transformation_matrix[3], m_rotation, glm::vec3(0, 1, 0));
    //+0.3f, 0.f, -0.2f
    m_geometric_transformation_matrix[3] =
        glm::translate(glm::mat4(1.0), glm::vec3(-0.3f, 0.f, +0.2f) + m_position) *
        glm::scale(glm::mat4(1.0), glm::vec3(0.1f))*
        glm::rotate(glm::mat4(1.0), m_rotation, glm::vec3(0, 1, 0));
    m_geometric_transformation_normal_matrix[3] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[3]))));

}

void Skeleton::setGoal(int goal)
{
    m_goal = goal;
}

void Skeleton::Move(float dt)
{
    float rotation;
    glm::vec3 delta_skeleton = m_road[m_goal].getPosition() - m_position;

    if (std::abs(delta_skeleton.z) < 0.02f && std::abs(delta_skeleton.x) < 0.02f && m_goal < m_road.size() - 1)
    {
        if (!(m_goal + 1 == m_road.size()))
        {
            setGoal(m_goal + 1);
        }
        else
        {
            std::cout << "Treasure reached!" << std::endl;
        }
    }

    //delta_skeleton *= dt * m_velocity;
    if(delta_skeleton.x > 0 && std::abs(delta_skeleton.x) > std::abs(delta_skeleton.z))
    {
        m_position.x += dt*m_velocity;
        //std::cout << "x>0" <<std::endl;

    }else if (delta_skeleton.x < 0 && std::abs(delta_skeleton.z) < std::abs(delta_skeleton.x))
    {
        m_position.x -= dt*m_velocity;
        //std::cout << "x<0" <<std::endl;

    }else if(delta_skeleton.z > 0 && std::abs(delta_skeleton.z) > std::abs(delta_skeleton.x))
    {
        //std::cout << "z>0" <<std::endl;
        m_position.z += dt*m_velocity;

    }else if (delta_skeleton.z < 0 && std::abs(delta_skeleton.z) > std::abs(delta_skeleton.x))
    {
        //std::cout << "z<0 "<<std::endl;
        m_position.z -= dt*m_velocity;

    }else
    {
        bool a = delta_skeleton.z > 0;
    }
    setPosition(m_position, 0);
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
