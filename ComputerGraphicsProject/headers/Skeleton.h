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
    Skeleton(glm::vec3 position, int goal, float hand_start_rotation, std::vector<Tile> &road, GeometryNode** g_node, int health);
	~Skeleton();
	
    void setPosition(glm::vec3 position, float rotation, float dt);

	void setGoal(int goal);

    void setVelocity(float velocity);

    float getVelocity();

	void Move(float dt, float continuous_time);

    void kill();
	
	glm::vec3 getPosition();

    glm::vec3 getCenterOfSphere();

    float getRadius();

	GeometryNode ** getGeometricNode();
	
    glm::mat4* getGeometricTransformationMatrix();
	
    glm::mat4* getGeometricTransformationNormalMatrix();

	int GetGoal();

    float distance_from_position(glm::vec3 cannonballs);

    float distance_from(glm::vec3 cannonballs);

    void lose_health(int i);

    int get_health();

    float get_max_health();

    void set_health(int health);

    void set_radious(float radius);



private:
	GeometryNode**			m_geometric_node;
	
	glm::mat4				m_geometric_transformation_matrix[6];
	glm::mat4				m_geometric_transformation_normal_matrix[6];
	glm::vec3				m_position;
    glm::vec3               m_center_of_sphere;

	int						m_goal;
    float                   m_velocity;
    float                   m_rotation;
	float					m_hand_start_rotation;
    int                     m_health;
    float                     m_max_health;
    float                   m_radius;
    float                   m_randomNumber;


	std::vector<Tile>		m_road;
};
