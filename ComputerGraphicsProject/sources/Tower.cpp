#include "../headers/Tower.h"
#include <map>

Tower::Tower()
{

}

Tower::Tower(glm::vec3 position, GeometryNode* g_node, int range) {
	setPosition(position);
	m_geometric_node = g_node;
    m_range = range;
}

void Tower::setPosition(glm::vec3 position) {
	m_position = position;
	m_geometric_transformation_matrix =
		glm::translate(glm::mat4(1.f), getPosition()) *
		glm::scale(glm::mat4(1.f), glm::vec3(0.25f));
	m_geometric_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_transformation_matrix))));
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

void Tower::shoot_closest(std::vector<Skeleton> &skeletons, int width, int height)
{
    std::map<float, size_t> in_range_skels;

    // loop over the total range of the tower
    for (int i = -m_range; i <= m_range; ++i)
    {
        for (int j = -m_range; j <= m_range; ++j)
        {
            float tile_x = m_position.x + i;
            float tile_z = m_position.z + j;
            // in bounds check
            //std::cout <<m_position.x << ", " << m_position.z << std::endl;

            //std::cout <<tile_x << ", " << tile_z << std::endl;
            if (tile_x < 0 || tile_x >= width || tile_z < 0 || tile_z >= width)
            {
                continue;
            }
            // this map is always ordered by the keys
            // now we have to see if a skeleton is in this tile
            //std::cout << "here" << std::endl;

            for (size_t i = 0; i < skeletons.size(); ++i)
            {
                float is_here = skeletons[i].distance_from(tile_x, tile_z);
                //std::cout << is_here << std::endl;
                if (is_here >= 0 && is_here <= 1)
                {
                    // distance from the tower
                    float distance2 = skeletons[i].distance_from(m_position.x, m_position.z);
                    in_range_skels[distance2] = i;
                }
            }
        }
    }
    if (in_range_skels.size() != 0)
    {
        auto closest = in_range_skels.begin();
        skeletons[closest->second].lose_health(1);
        std::cout << "the tower shoots the closest skeleton " << std::endl;
    }
}
