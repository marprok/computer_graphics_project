#ifndef CHEST_H
#define CHEST_H

#endif // CHEST_H
#pragma once

#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    #ifdef _WIN64
        //define something for Windows (64-bit only)
        #include "glm/gtc/type_ptr.hpp"
        #include "glm/gtc/matrix_transform.hpp"
        #include "GeometryNode.h"
        #include <vector>
        #include "Skeleton.h"
    #endif
#elif __APPLE__
    // apple
    #include "TargetConditionals.h"
    #include "../glm/gtc/type_ptr.hpp"
    #include "../glm/gtc/matrix_transform.hpp"
    #include "GeometryNode.h"
    #include <vector>
    #include "AudioSystem.h"
    #include "Skeleton.h"
#elif __linux__
    // linux
    #include "../glm/gtc/type_ptr.hpp"
    #include "../glm/gtc/matrix_transform.hpp"
    #include "GeometryNode.h"
    #include <vector>
    #include "AudioSystem.h"
    #include "Skeleton.h"
#endif

class Chest
{
public:
    Chest();
    Chest(GeometryNode* g_node);
    ~Chest();

    void setPosition(glm::vec3 position);

    glm::vec3 getPosition();

    GeometryNode* getGeometricNode();

    glm::mat4 getGeometricTransformationMatrix();

    glm::mat4 getGeometricTransformationNormalMatrix();

    void setTransformationMatrix(glm::mat4 transformationMatrix);

    void setTransformationNormalMatrix(glm::mat4 transformationNormalMatrix);

    void lose_coins();

    bool isReached(std::vector<Skeleton> &skeletons);

    int getCoinsLeft();

    void add_coins(int coins);


private:
    glm::vec3				m_position;
    glm::mat4				m_geometric_transformation_matrix;
    glm::mat4				m_geometric_transformation_normal_matrix;
    GeometryNode*			m_geometric_node;
    int                     m_coins_left;
    float                   m_radius;
    int                     m_first_skeleton;
};
