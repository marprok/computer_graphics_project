#include "../headers/ParticleSystem.h"
#include "GeometryNode.h"
#include "Tools.h"
#include <algorithm>
#include "ShaderProgram.h"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "OBJLoader.h"
#include "../headers/TextureManager.h"
#include <iostream>


ParticleEmitter::ParticleEmitter(glm::vec3 expos)
{
	m_continous_time = 0.0;
	m_vbo = 0;
    m_explosion_position = expos;
	m_vao = 0;
}

ParticleEmitter::~ParticleEmitter()
{

}

ParticleEmitter::ParticleEmitter()
{
    m_continous_time = 0.0;
    m_vbo = 0;
    m_vao = 0;
}

bool ParticleEmitter::Init()
{
    m_particles_position.resize(100);
	m_particles_velocity.resize(120);
    m_particles_life.resize(120, 0.f);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_particles_position.size() * sizeof(glm::vec3), &m_particles_position[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,				// attribute index
        3,              // number of elements per vertex, here (x,y,z)
		GL_FLOAT,       // the type of each element
		GL_FALSE,       // take our values as-is
		0,		         // no extra data between each position
		0				// pointer to the C array or an offset to our buffer
	);

	//If there was any errors
	if (Tools::CheckGLError() != GL_NO_ERROR)
	{
		printf("Exiting with error at Renderer::Init\n");
		return false;
	}

	//If everything initialized
	return true;
}

void ParticleEmitter::Update(float dt)
{
    float movement_speed = 6.f;

    for (int i = 0; i < m_particles_position.size(); ++i)
	{
		if (m_particles_life[i] <= 0.f)
		{
			// the life will be a random value between [0.5 ... 1.0]
            m_particles_life[i] = 0.5f * rand() / float(RAND_MAX) + 0.5f;
            //m_particles_life[i]=0.1;
			// Create a velocity.
			m_particles_velocity[i] = glm::vec3(rand(), rand(), rand()) / float(RAND_MAX);
			m_particles_velocity[i] = glm::normalize(m_particles_velocity[i]);

			float angle = glm::radians(360.f * rand() / float(RAND_MAX));
			m_particles_position[i] = glm::vec3(0, 1, 0);


			// the life will be a random value between [0.5 ... 1.0]
			m_particles_life[i] = 0.5f * rand() / float(RAND_MAX) + 0.5f;
			// Create a random velocity. XZ components of velocity will be random numbers between [0...1].
			m_particles_velocity[i] = glm::vec3(rand(), RAND_MAX, rand()) / float(RAND_MAX);
			// Change velocity (X,Y,Z) from [0...1] range to [-1...1]
			m_particles_velocity[i] = 2.f * m_particles_velocity[i] - 1.f;
			// Make the velocity cone smaller
			m_particles_velocity[i] *= 0.5f;
			m_particles_velocity[i].y = 1.f;
			// normalize the velocity vector
			m_particles_velocity[i] = glm::normalize(m_particles_velocity[i]);

            //emitter position
            m_particles_position[i] = m_explosion_position;

		}
		else
		{
			// reduce the life
			m_particles_life[i] -= dt;
			// update the position using the velocity vector
			m_particles_position[i] += m_particles_velocity[i] * movement_speed * dt;
		}
	}

	// Reupload data to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_particles_position.size() * sizeof(glm::vec3), &m_particles_position[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	m_continous_time += dt;
}

void ParticleEmitter::Render()
{
	glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(1);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, (GLsizei)m_particles_position.size());
}

glm::vec3 ParticleEmitter::getPosition()
{
    return m_explosion_position;
}

void ParticleEmitter::setPosition(glm::vec3 position)
{
    m_explosion_position = position;
}

float ParticleEmitter::get_continuous_time()
{
    return m_continous_time;
}
