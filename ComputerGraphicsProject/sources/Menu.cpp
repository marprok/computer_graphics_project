#include "../headers/Menu.h"
#include <map>

Menu::Menu(GeometryNode* g_node)
{
    m_geometric_node = g_node;
}



void Menu::SetPosition(glm::vec3 position) {
    m_position = position;
    m_geometric_transformation_matrix =
        glm::translate(glm::mat4(1.f), m_position) *
            glm::rotate(glm::mat4(1.0f), 0.4f, glm::vec3(0, 1, 0 )) *
        glm::rotate(glm::mat4(1.0f), -1.0f, glm::vec3(1, 0, 0)) *
        glm::scale(glm::mat4(1.f), glm::vec3(0.2f));
    m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
}


Menu::~Menu()
{
}

glm::vec3 Menu::getPosition() {
    return m_position;
}

GeometryNode* Menu::getGeometricNode() {
    return m_geometric_node;
}

glm::mat4 Menu::getGeometricTransformationMatrix()
{
    return m_geometric_transformation_matrix;
}

void Menu::setTransformationMatrix(glm::mat4 transformationMatrix)
{
    m_geometric_transformation_matrix = transformationMatrix;
}

void Menu::setTransformationNormalMatrix(glm::mat4 transformationNormalMatrix)
{
    m_geometric_transformation_normal_matrix = transformationNormalMatrix;
}

glm::mat4 Menu::getGeometricTransformationNormalMatrix()
{
    return m_geometric_transformation_normal_matrix;
}

