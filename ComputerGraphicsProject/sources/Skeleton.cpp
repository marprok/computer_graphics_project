#include "../headers/Skeleton.h"

#define PI 3.14159f

Skeleton::Skeleton()
{
}

Skeleton::Skeleton(glm::vec3 position, int goal, float hand_start_rotation, std::vector<Tile> &road, GeometryNode ** g_node, int health)
{
    setPosition(position, 0, 0);
    setGoal(goal);
    m_center_of_sphere = glm::vec3(-0.06082, 0.962787, -0.089274);
    m_road = road;
    m_radius = 0.4f;
    m_rotation = 3.14f;
    m_velocity = 2.f;
    //m_randomNumber = ((float)rand() / RAND_MAX) * 2.0f;
    m_randomNumber = 0;
    m_geometric_node = g_node;
	m_hand_start_rotation = hand_start_rotation;
    m_health = health;
    m_max_health = health;

}

void Skeleton::setPosition(glm::vec3 position, float angle, float continuous_time) {
    m_position = position;
	m_rotation = angle;
    m_position.y = 0.002f;

	glm::mat4 pirate_position;
	pirate_position =
		glm::translate(glm::mat4(1.0f), m_position) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.11, 0)) *
		glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 1, 0)) *
        glm::scale(glm::mat4(1.0), glm::vec3(0.06f));

    // body
    m_geometric_transformation_matrix[0] = pirate_position;
    m_geometric_transformation_normal_matrix[0] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[0]))));

    // arm
	m_geometric_transformation_matrix[1] =
		pirate_position *
		glm::translate(glm::mat4(1.0), glm::vec3(4.5f, 12.f, 0.f)) *
		glm::rotate(glm::mat4(1.0), 0.8f * std::sin(2 * m_velocity * continuous_time), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0), m_hand_start_rotation, glm::vec3(1, 0, 0)) *
		glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -3.f));

    m_geometric_transformation_normal_matrix[1] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[1]))));


    // right foot
    m_geometric_transformation_matrix[2] =
		pirate_position *
        glm::translate(glm::mat4(1.0), glm::vec3(-4.f, 0.f, -2.f * std::sin(continuous_time * 4 * m_velocity)));

    m_geometric_transformation_normal_matrix[2] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[2]))));

    // left foot
    m_geometric_transformation_matrix[3] =
		pirate_position *
        glm::translate(glm::mat4(1.0), glm::vec3(4.f, 0, 2.f * std::sin(continuous_time * 4 * m_velocity)));
    m_geometric_transformation_normal_matrix[3] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[3]))));

    float bar_scale_factor = get_health() / m_max_health /*max_health*/;
    //std::cout << "remaing life = " << bar_scale_factor << std::endl;
	// green health bar
	m_geometric_transformation_matrix[4] =
		pirate_position *
		glm::translate(glm::mat4(1.0), glm::vec3(-7, 26, 0)) *
		glm::scale(glm::mat4(1.0), glm::vec3((get_health() == 0) ? 0.f : bar_scale_factor, 1.f, 1.f));
	m_geometric_transformation_normal_matrix[4] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[4]))));

	// red health bar
	m_geometric_transformation_matrix[5] =
		pirate_position *
		glm::translate(glm::mat4(1.0), glm::vec3(7, 26, 0));
	
	if (bar_scale_factor < 1 /*max_health*/)
	{
		m_geometric_transformation_matrix[5] *=
			glm::scale(glm::mat4(1.0), glm::vec3((get_health() == 0) ? 0.f : (1 - bar_scale_factor), 1.f, 1.f));
	}

	m_geometric_transformation_normal_matrix[5] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[5]))));

}

void Skeleton::kill()
{

    glm::vec3 random_position = m_position;
    random_position.x += m_randomNumber;
    random_position.z += m_randomNumber;
    // body
    m_geometric_transformation_matrix[0] =

            glm::translate(glm::mat4(1.0), glm::vec3(0, 0.2f, 0) + random_position)*
            glm::rotate(glm::mat4(1.0f), 1.57f, glm::vec3(1, 0, 0) ) *
            glm::scale(glm::mat4(1.0), glm::vec3(0.06f));
    m_geometric_transformation_normal_matrix[0] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[0]))));

    // arm
    m_geometric_transformation_matrix[1] =
            glm::translate(glm::mat4(1.0), glm::vec3(1.0f, 0.f, 0) + random_position)*
            glm::rotate(glm::mat4(1.0f), 1.57f, glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1.0), glm::vec3(0.06f));
    m_geometric_transformation_normal_matrix[1] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[1]))));

    // right foot
    m_geometric_transformation_matrix[2] =
            glm::translate(glm::mat4(1.0), glm::vec3(1.0f, 0.f, 0) + random_position)*
            glm::scale(glm::mat4(1.0), glm::vec3(0.06f));
    m_geometric_transformation_normal_matrix[2] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[2]))));

    // left foot
    m_geometric_transformation_matrix[3] =
            glm::translate(glm::mat4(1.0), glm::vec3(1.0f, 0.f, 0) + random_position)*
            glm::scale(glm::mat4(1.0), glm::vec3(0.06f));
    m_geometric_transformation_normal_matrix[3] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix[3]))));
}

void Skeleton::setGoal(int goal)
{
    m_goal = goal;
}

void Skeleton::Move(float dt, float continuous_time)
{
    if(m_health !=0)
    {
        float rotation;
        glm::vec3 delta_skeleton = m_road[m_goal].getPosition() - m_position;

        if (std::abs(delta_skeleton.z) < 0.2f && std::abs(delta_skeleton.x) < 0.2f && m_goal < m_road.size() - 1)
        {
            if (!(m_goal + 1 == m_road.size()))
            {
                setGoal(m_goal + 1);
                delta_skeleton = m_road[m_goal].getPosition() - m_position;
            }
            else
            {
                std::cout << "Treasure reached!" << std::endl;
            }
        }

        float angle = 0.f;
        //delta_skeleton *= dt * m_velocity;
        if(delta_skeleton.x > 0 && std::abs(delta_skeleton.x) > std::abs(delta_skeleton.z))
        {
            m_position.x += dt*m_velocity;
            angle = 3 * PI / 2;
            //std::cout << "x>0" <<std::endl;

        }else if (delta_skeleton.x < 0 && std::abs(delta_skeleton.z) < std::abs(delta_skeleton.x))
        {
            m_position.x -= dt*m_velocity;
            angle = PI / 2;
            //std::cout << "x<0" <<std::endl;

        }else if(delta_skeleton.z > 0 && std::abs(delta_skeleton.z) > std::abs(delta_skeleton.x))
        {
            //std::cout << "z>0" <<std::endl;
            m_position.z += dt*m_velocity;
            angle = PI;

        }else if (delta_skeleton.z < 0 && std::abs(delta_skeleton.z) > std::abs(delta_skeleton.x))
        {
            //std::cout << "z<0 "<<std::endl;
            m_position.z -= dt*m_velocity;

        }

        setPosition(m_position, angle, continuous_time);
    }

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

glm::vec3 Skeleton::getCenterOfSphere()
{
    return m_center_of_sphere + m_position;
}

float Skeleton::getRadius()
{
    return m_radius;
}

Skeleton::~Skeleton()
{
}

float Skeleton::distance_from(glm::vec3 cannonball)
{
    glm::vec3 m = getCenterOfSphere();
    float distance = std::sqrt((m.x - cannonball.x)*(m.x - cannonball.x) + (m.z - cannonball.z)*(m.z - cannonball.z) + (m.y - cannonball.y)*(m.y - cannonball.y));
    return distance;
}

float Skeleton::distance_from_position(glm::vec3 cannonball)
{
    float distance = std::sqrt((m_position.x - cannonball.x)*(m_position.x - cannonball.x) + (m_position.z - cannonball.z)*(m_position.z - cannonball.z));
    return distance;
}

void Skeleton::lose_health(int i)
{

    m_health = (m_health - i < 0) ? 0 : m_health - i;
    std::cout << "health = " << m_health << std::endl;
}

int Skeleton::get_health()
{
    return m_health;
}

void Skeleton::set_health(int health)
{
    m_health = health;
}

float Skeleton::get_max_health() { return m_max_health; }
