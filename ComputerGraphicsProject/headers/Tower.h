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

class Tower
{
public:
	Tower();
    Tower(glm::vec3 position, GeometryNode* g_node, int range);
	~Tower();

	void setPosition(glm::vec3 position);

	glm::vec3 getPosition();

	GeometryNode* getGeometricNode();

	glm::mat4 getGeometricTransformationMatrix();

	glm::mat4 getGeometricTransformationNormalMatrix();

    void shoot_closest(std::vector<Skeleton> &skeletons, int width, int height);

private:
	glm::vec3				m_position;
	glm::mat4				m_geometric_transformation_matrix;
	glm::mat4				m_geometric_transformation_normal_matrix;
    int                     m_range; // the number of tiles in one direction
	GeometryNode*			m_geometric_node;
};
