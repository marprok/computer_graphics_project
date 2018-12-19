#include "../headers/SpotlightNode.h"
#include "glm\gtc\matrix_transform.hpp"
#include "../headers/Tools.h"

// Spot Light
SpotLightNode::SpotLightNode()
{
	m_name = "defaultSpotLight1";

	SetColor(glm::vec3(1.0f));
	SetPosition(glm::vec3(5, 3, 0));
	SetTarget(glm::vec3(0, 0, 0));
	// umbra and penumbra in degrees
	SetConeSize(60, 60);

	m_cast_shadow = false;
	m_shadow_map_resolution = 1024;
	m_shadow_map_bias = 0.001;
	m_shadow_map_texture = 0;
	m_shadow_map_fbo = 0;
}

SpotLightNode::~SpotLightNode()
{
	glDeleteFramebuffers(1, &m_shadow_map_fbo);
	glDeleteTextures(1, &m_shadow_map_texture);
}

void SpotLightNode::CastShadow(bool cast)
{
	m_cast_shadow = cast;
	
	if (cast)
	{
		if(m_shadow_map_texture == 0)
			glGenTextures(1, &m_shadow_map_texture);
		// Depth buffer
		glBindTexture(GL_TEXTURE_2D, m_shadow_map_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_shadow_map_resolution, m_shadow_map_resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D, 0);

		if(m_shadow_map_fbo == 0)
			glGenFramebuffers(1, &m_shadow_map_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_shadow_map_fbo);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadow_map_texture, 0);

		GLenum status = Tools::CheckFramebufferStatus(m_shadow_map_fbo);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("Error in Spotlight shadow FB generation.\n");
			return;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void SpotLightNode::SetColor(glm::vec3 color)
{
	m_light_color = color;
}

void SpotLightNode::SetPosition(glm::vec3 pos)
{
	m_light_position = pos;
	m_light_direction = glm::normalize(m_light_target - m_light_position);
	m_view_matrix = glm::lookAt(m_light_position, m_light_target, glm::vec3(0, 1, 0));
	m_view_inverse_matrix = glm::inverse(m_view_matrix);
}

void SpotLightNode::SetTarget(glm::vec3 target)
{
	m_light_target = target;
	m_light_direction = glm::normalize(m_light_target - m_light_position);
	m_view_matrix = glm::lookAt(m_light_position, m_light_target, glm::vec3(0, 1, 0));
	m_view_inverse_matrix = glm::inverse(m_view_matrix);
}

void SpotLightNode::SetConeSize(float umbra, float penumbra)
{
	m_umbra = umbra;
	m_penumbra = penumbra;

	float near_clipping_range = 0.1f;
	float far_clipping_range = 1500.f;

	// create a frustum that  encapsulate the light cone
	float h = near_clipping_range * glm::tan(glm::radians(m_penumbra * 0.5f));
	m_projection_matrix = glm::frustum(-h, h, -h, h, near_clipping_range, far_clipping_range);
	m_projection_inverse_matrix = glm::inverse(m_projection_matrix);
}

glm::vec3 SpotLightNode::GetPosition()
{
	return m_light_position;
}

glm::vec3 SpotLightNode::GetDirection()
{
	return m_light_direction;
}

glm::vec3 SpotLightNode::GetColor()
{
	return m_light_color;
}

float SpotLightNode::GetUmbra() 
{
	return m_umbra;
}

float SpotLightNode::GetPenumbra()
{
	return m_penumbra;
}

bool SpotLightNode::GetCastShadowsStatus()
{
	return m_cast_shadow;
}

GLuint SpotLightNode::GetShadowMapFBO()
{
	return m_shadow_map_fbo;
}

GLuint SpotLightNode::GetShadowMapDepthTexture()
{
	return m_shadow_map_texture;
}

int SpotLightNode::GetShadowMapResolution()
{
	return m_shadow_map_resolution;;
}

glm::mat4 SpotLightNode::GetProjectionMatrix()
{
	return m_projection_matrix;
}

glm::mat4 SpotLightNode::GetViewMatrix()
{
	return m_view_matrix;
}