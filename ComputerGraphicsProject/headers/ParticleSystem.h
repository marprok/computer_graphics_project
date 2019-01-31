#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    #ifdef _WIN64
    //define something for Windows (64-bit only)
    #include "GLEW/glew.h"
    #include "glm/glm.hpp"
    #include <vector>
    #include "ShaderProgram.h"
    #endif
#elif __APPLE__
    // apple
    #include "../GLEW/glew.h"
    #include "../glm/glm.hpp"
    #include <vector>
    #include "ShaderProgram.h"
#elif __linux__
    #include "../GLEW/glew.h"
    #include "../glm/glm.hpp"
    #include <vector>
    #include "ShaderProgram.h"
#endif


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
