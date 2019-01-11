#pragma once
#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
		//define something for Windows (64-bit only)
		#include "glm/gtc/type_ptr.hpp"
		#include "glm/gtc/matrix_transform.hpp"
		#include "GeometryNode.h"
		#include "Tile.h"
		#include <iostream>
	#endif
#elif __APPLE__
	// apple
	#include "TargetConditionals.h"
	#include "../glm/gtc/type_ptr.hpp"
	#include "../glm/gtc/matrix_transform.hpp"
	#include "GeometryNode.h"
	#include "Tile.h"
	#include <iostream>
#elif __linux__
	// linux
	#include "../glm/gtc/type_ptr.hpp"
	#include "../glm/gtc/matrix_transform.hpp"
	#include "GeometryNode.h"
	#include "Tile.h"
	#include <iostream>
#endif

class Skeleton
{
public:
	Skeleton();
	Skeleton(glm::vec3 position, int goal, std::vector<Tile> &road, GeometryNode** g_node);
	~Skeleton();
	
    void setPosition(glm::vec3 position, float rotation);

	void setGoal(int goal);

    void setVelocity(float velocity);

    float getVelocity();

	void Move(float dt);
	
	glm::vec3 getPosition();
	
	GeometryNode ** getGeometricNode();
	
	glm::mat4* getGeometricTransformationMatrix();
	
	glm::mat4* getGeometricTransformationNormalMatrix();

	int GetGoal();



private:
	GeometryNode**			m_geometric_node;
	
	glm::mat4				m_geometric_transformation_matrix[4];
	glm::mat4				m_geometric_transformation_normal_matrix[4];
	glm::vec3				m_position;

	int						m_goal;
    float                   m_velocity;
    float                   m_rotation;

	std::vector<Tile>		m_road;
};
