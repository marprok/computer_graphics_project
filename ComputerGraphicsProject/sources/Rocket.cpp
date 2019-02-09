#include "../headers/Rocket.h"
#include <map>
#define PI 3.14159f
Rocket::Rocket()
{

}

Rocket::Rocket(glm::vec3 position, GeometryNode* g_node, int target, float speed, glm::vec3 goal) {
    m_geometric_node = g_node;
    position.y = 2.0f;
    setPosition(position, 0, 0);
    m_radius = 0.05f;
    m_target = target;
    m_center_of_sphere = m_position;
    m_speed = speed;
	m_goal = goal;
	m_direction = m_goal - m_position;
}

void Rocket::setPosition(glm::vec3 position, float theta, float theta_z) {
    m_position = position;
    m_geometric_transformation_matrix =
        glm::translate(glm::mat4(1.f), getPosition()) *
        glm::rotate(glm::mat4(1.f), theta, glm::vec3(0, 1, 0)) *
        glm::rotate(glm::mat4(1.f), theta_z, glm::vec3(0, 0, 1)) *
        glm::rotate(glm::mat4(1.f), PI / 2.f, glm::vec3(1, 0, 0)) *
        glm::scale(glm::mat4(1.f), glm::vec3(0.15f));
    m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
}



bool Rocket::update(float dt, std::vector<Skeleton> &skeletons)
{

    if (skeletons.size() <= m_target)
    {
        return false;
    }

    glm::vec3 skeleton_pos = skeletons[m_target].getCenterOfSphere();

    // d = sqrt((x1 - x0) ^ 2 + (z1 - z0) ^ 2)
    float d = std::sqrt(
        ((skeleton_pos.x - m_position.x) * (skeleton_pos.x - m_position.x)) +
        ((skeleton_pos.z - m_position.z) * (skeleton_pos.z - m_position.z))
    );

    // ratio: used for triangle similarity
    float t = (m_speed * dt) / d;

    // new_x = x0 * (1 - t) + t * x1
    m_position.x = m_position.x * (1 - t) + t * skeleton_pos.x;

    // new_y = y0 * (1 - t) + t * y1
    m_position.y = m_position.y * (1 - t) + t * skeleton_pos.y;

    // new_z = z0 * (1 - t) + t * z1
    m_position.z = m_position.z * (1 - t) + t * skeleton_pos.z;

    // theta is in rads
    float theta = std::atan2(skeleton_pos.x - m_position.x, skeleton_pos.z - m_position.z);
    float theta_z = std::atan2(skeleton_pos.y - m_position.y, skeleton_pos.z - m_position.z);

    setPosition(m_position, theta, theta_z);
    m_center_of_sphere = m_position;

    for (auto &skeleton : skeletons)
    {
        float distance = skeleton.distance_from(m_center_of_sphere);
        if (distance <= (m_radius + skeleton.getRadius()))
        {
            if (skeleton.get_health() > 0)
            {
                skeleton.lose_health(3);
                Audio::PlayAudio("explosion.wav");
            }
            else
            {
                // The skeleton is dead
                // Set radious to 0 so that it won' t affect next cannonballs
                skeleton.set_radious(0);
            }

            return false;
        }
    }
    return true;

}


glm::vec3 Rocket::getPosition() {
    return m_position;
}

GeometryNode* Rocket::getGeometricNode() {
    return m_geometric_node;
}

glm::mat4 Rocket::getGeometricTransformationMatrix()
{
    return m_geometric_transformation_matrix;
}

glm::mat4 Rocket::getGeometricTransformationNormalMatrix()
{
    return m_geometric_transformation_normal_matrix;
}

int Rocket::get_target()
{
    return m_target;
}

Rocket::~Rocket()
{
}


