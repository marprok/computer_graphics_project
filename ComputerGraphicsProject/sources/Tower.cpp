#include "../headers/Tower.h"
#include <map>

Tower::Tower()
{

}

Tower::Tower(glm::vec3 position, GeometryNode* g_node, int range, float threshold) {
	setPosition(position);
	m_geometric_node = g_node;
    m_range = range;
    m_shoot_threshold = threshold;
    m_shoot_timer = 0.0f;
    m_to_be_removed=false;
}

void Tower::setPosition(glm::vec3 position) {
	m_position = position;
	m_geometric_transformation_matrix =
		glm::translate(glm::mat4(1.f), getPosition()) *
		glm::scale(glm::mat4(1.f), glm::vec3(0.25f));
	m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
}

void Tower::Remove(float dt)
{
    glm::vec3 new_position = m_position;
    new_position.y -= dt*4;
    setPosition(new_position);
}

glm::vec3 Tower::getPosition() {
	return m_position;
}

GeometryNode* Tower::getGeometricNode() {
	return m_geometric_node;
}

glm::mat4 Tower::getGeometricTransformationMatrix()
{
	return m_geometric_transformation_matrix;
}

glm::mat4 Tower::getGeometricTransformationNormalMatrix()
{
	return m_geometric_transformation_normal_matrix;
}

Tower::~Tower()
{
}

int Tower::shoot_closest(std::vector<Skeleton> &skeletons, int width, int height, float dt)
{
    if(!m_to_be_removed)
    {
        //std::cout << m_position.x << " pos " << m_position.z << std::endl;
        std::map<float, size_t> in_range_skels;
        // loop over the total range of the tower
        for (int i = -m_range; i <= m_range; ++i)
        {
            for (int j = -m_range; j <= m_range; ++j)
            {
                glm::vec3 tile_pos;
                float tile_x = m_position.x + 2*i;
                float tile_z = m_position.z + 2*j;
                tile_pos.x = tile_x;
                tile_pos.z = tile_z;
                tile_pos.y = 0.0f;
                // in bounds check


                if (tile_pos.x < 0 || tile_pos.x  >= width || tile_pos.z < 0 || tile_pos.z >= width)
                {
                    continue;
                }
                //std::cout <<tile_x << ", " << tile_z << std::endl;
                // this map is always ordered by the keys
                // now we have to see if a skeleton is in this tile
                //std::cout << "here" << std::endl;

                for (size_t i = 0; i < skeletons.size(); ++i)
                {
                    float is_here = skeletons[i].distance_from_position(tile_pos);
                    //std::cout << is_here << std::endl;
                    if (is_here <= 1.0f && skeletons[i].get_health() !=0)
                    {
                        //std::cout << "here" << std::endl;
                        // distance from the tower
                        float distance2 = skeletons[i].distance_from(m_position);
                        in_range_skels[distance2] = i;
                    }
                }
            }
        }
        m_shoot_timer += dt;
        if (in_range_skels.size() != 0 && m_shoot_timer >= m_shoot_threshold)
        {
            auto closest = in_range_skels.begin();
            m_shoot_timer = 0.0f;
            //std::cout << "the tower shoots the closest skeleton " << std::endl;
            return closest->second;
        }
    }
    //std::exit(1);
    return -1;
}

bool Tower::to_be_removed()
{
    return m_to_be_removed;
}

void Tower::set_to_be_removed(bool flag)
{
    m_to_be_removed=flag;
}
