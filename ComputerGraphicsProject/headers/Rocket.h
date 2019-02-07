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
    #include "Skeleton.h"
#elif __linux__
	// linux
	#include "../glm/gtc/type_ptr.hpp"
	#include "../glm/gtc/matrix_transform.hpp"
	#include "GeometryNode.h"
    #include <vector>
    #include "Skeleton.h"
#endif

class Rocket
{
public:
    Rocket();
    Rocket(glm::vec3 position, GeometryNode* g_node, int target, float speed, glm::vec3 goal);
    ~Rocket();

    void setPosition(glm::vec3 position, float theta, float theta_z);

    bool update(float dt, std::vector<Skeleton> &skeletons);

	glm::vec3 getPosition();

	GeometryNode* getGeometricNode();

	glm::mat4 getGeometricTransformationMatrix();

    glm::mat4 getGeometricTransformationNormalMatrix();

    int get_target();


private:
	glm::vec3				m_position;
	glm::mat4				m_geometric_transformation_matrix;
	glm::mat4				m_geometric_transformation_normal_matrix;
	GeometryNode*			m_geometric_node;
    glm::vec3               m_center_of_sphere;
    glm::vec3               m_initial_position;
	glm::vec3				m_goal;
	glm::vec3				m_direction;

    int                     m_target;
    float                   m_speed;
    float                   m_radius;
    int                     i;

};
