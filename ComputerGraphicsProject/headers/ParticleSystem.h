#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "../GLEW/glew.h"
#include "../glm/glm.hpp"
#include <vector>
#include "../headers/ShaderProgram.h"


class ParticleEmitter
{
protected:
	std::vector<glm::vec3>							m_particles_position;
	std::vector<glm::vec3>							m_particles_velocity;
	std::vector<float>								m_particles_life;
    glm::vec3                                       m_explosion_position;

	// Store Particle Data on the GPU
	GLuint											m_vbo;
	GLuint											m_vao;

	float m_continous_time;

public:
    ParticleEmitter();
    ParticleEmitter(glm::vec3 explosion_position);
	~ParticleEmitter();
	bool										Init();
    void										Update(float dt);
	void										Render();
    glm::vec3                                   getPosition();
    void                                        setPosition(glm::vec3 position);
    float                                       get_continuous_time();
};

#endif
