#pragma once

#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
    #include "TargetConditionals.h"
    #include "../glm/gtc/type_ptr.hpp"
    #include "../glm/gtc/matrix_transform.hpp"
    #include "GeometryNode.h"
    #include <vector>
    #include "AudioSystem.h"
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
    #include "TargetConditionals.h"
    #include "../glm/gtc/type_ptr.hpp"
    #include "../glm/gtc/matrix_transform.hpp"
    #include "GeometryNode.h"
    #include <vector>
    #include "AudioSystem.h"
    #include "Skeleton.h"

#endif

class Menu
{
public:
    Menu(GeometryNode* g_node);
    ~Menu();

    void SetPosition(glm::vec3 position);

    glm::vec3 getPosition();

    void setTransformationMatrix(glm::mat4 transformationMatrix);

    void setTransformationNormalMatrix(glm::mat4 transformationNormalMatrix);

    GeometryNode* getGeometricNode();

    glm::mat4 getGeometricTransformationMatrix();

    glm::mat4 getGeometricTransformationNormalMatrix();

private:
    glm::vec3				m_position;
    glm::mat4				m_geometric_transformation_matrix;
    glm::mat4				m_geometric_transformation_normal_matrix;
    GeometryNode*			m_geometric_node;


};
