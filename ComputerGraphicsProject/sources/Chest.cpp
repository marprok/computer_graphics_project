#include "../headers/Chest.h"
#include <map>


Chest::Chest()
{

}

Chest::Chest(GeometryNode* g_node) {
    m_geometric_node = g_node;
    m_radius = 0.3f;
    m_first_skeleton=0;
    m_coins_left = 30;
}

void Chest::setPosition(glm::vec3 position) {
    m_position = position;
    m_geometric_transformation_matrix =
        glm::translate(glm::mat4(1.f), getPosition()) *
        glm::scale(glm::mat4(1.f), glm::vec3(0.05f));
    m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
}

bool Chest::isReached(std::vector<Skeleton> &skeletons)
{
    int size = skeletons.size();
    for(int i=0; i<size; i++)
    {
        float distance = skeletons[i].distance_from(m_position);
        if(distance <= (m_radius + skeletons[i].getRadius()) && skeletons[i].get_health()!=-2)
        {
            skeletons[i].set_health(-1);
            lose_coins();
            return true;
        }
    }
    return false;
}

glm::vec3 Chest::getPosition() {
    return m_position;
}

GeometryNode* Chest::getGeometricNode() {
    return m_geometric_node;
}

glm::mat4 Chest::getGeometricTransformationMatrix()
{
    return m_geometric_transformation_matrix;
}

glm::mat4 Chest::getGeometricTransformationNormalMatrix()
{
    return m_geometric_transformation_normal_matrix;
}

void Chest::setTransformationMatrix(glm::mat4 transformationMatrix)
{
    m_geometric_transformation_matrix = transformationMatrix;
}

void Chest::setTransformationNormalMatrix(glm::mat4 transformationNormalMatrix)
{
    m_geometric_transformation_normal_matrix = transformationNormalMatrix;
}

void Chest::lose_coins()
{
    m_coins_left -= 10;
    if(m_coins_left>=0)
    {
		Audio::PlayAudio("Coins.wav");
    }
    std::cout<<"Coins left: "<< m_coins_left<<std::endl;
}

int Chest::getCoinsLeft()
{
    return m_coins_left;
}

void Chest::add_coins(int coins)
{
    m_coins_left+=coins;
}

Chest::~Chest()
{
}


