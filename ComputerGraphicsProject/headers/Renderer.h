#ifndef BIM_ENGINE_RENDERER_H
#define BIM_ENGINE_RENDERER_H

#ifdef _WIN32
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
		//define something for Windows (64-bit only)
		#include "GLEW\glew.h"
		#include "glm\glm.hpp"
		#include <vector>
		#include "ShaderProgram.h"
		#include "SpotlightNode.h"
		#include "Tower.h"
		#include "Tile.h"
        #include "Menu.h"
        #include "Rocket.h"
        #include "ParticleSystem.h"
        #include "Cannonball.h"
		#include "Skeleton.h"
        #include "Chest.h"
        #include "AudioSystem.h"
	#endif
#elif __APPLE__
	// apple
	#include "TargetConditionals.h"
	#include "../GLEW/glew.h"
	#include "../glm/glm.hpp"
	#include <vector>
	#include "ShaderProgram.h"
	#include "SpotlightNode.h"
	#include "Tower.h"
    #include "Rocket.h"
    #include "ParticleSystem.h"
	#include "Tile.h"
    #include "Menu.h"
    #include "Chest.h"
    #include "Cannonball.h"
	#include "Skeleton.h"
    #include <AudioSystem.h>


#elif __linux__
	// linux
	#include "../GLEW/glew.h"
	#include "../glm/glm.hpp"
	#include <vector>
	#include "ShaderProgram.h"
	#include "SpotlightNode.h"
	#include "Tower.h"
    #include "Rocket.h"
    #include "Menu.h"
    #include "ParticleSystem.h"
    #include "Cannonball.h"
	#include "Tile.h"
	#include "Skeleton.h"
    #include "Chest.h"
    #include "AudioSystem.h"
#endif

class Renderer
{
public:
	enum RENDERING_MODE
	{
		TRIANGLES,
		LINES,
		POINTS
	};

protected:
	int												m_screen_width, m_screen_height;
	glm::mat4										m_view_matrix;
	glm::mat4										m_projection_matrix;
	glm::vec3										m_camera_position;
    glm::vec3                                       m_camera_position_temp;
	glm::vec3										m_camera_target_position;
	glm::vec3										m_camera_up_vector;
	glm::vec2										m_camera_movement;
	glm::vec2										m_camera_look_angle_destination;
	
	// Geometry Rendering Intermediate Buffer
	GLuint m_fbo;
	GLuint m_fbo_depth_texture;
	GLuint m_fbo_texture;
	
	GLuint m_vao_fbo, m_vbo_fbo_vertices;

	float m_continuous_time;

	// Rendering Mode
	RENDERING_MODE m_rendering_mode;

	// Lights
	SpotLightNode m_spotlight_node;
    SpotLightNode m_menu_light;

	// Meshes
    class GeometryNode*								m_terrain;
    glm::mat4										m_terrain_transformation_matrix;
    glm::mat4										m_terrain_transformation_normal_matrix;
	
    class GeometryNode*								m_chest_object;
    glm::mat4										m_chest_object_transformation_matrix;
    glm::mat4										m_chest_object_transformation_normal_matrix;
	
    class GeometryNode*								m_tower_object;
    glm::mat4										m_tower_object_transformation_matrix;
    glm::mat4										m_tower_object_transformation_normal_matrix;
	
    class GeometryNode*								m_road_object;
    glm::mat4										m_road_object_transformation_matrix;
    glm::mat4										m_road_object_transformation_normal_matrix;
	
    class GeometryNode*								m_green_tile;
    glm::mat4										m_player_tile_transformation_matrix;
    glm::mat4										m_player_tile_transformation_normal_matrix;
    glm::vec3										m_player_tile_position;

    class GeometryNode*								m_skeleton_object[6];
    glm::mat4										m_skeleton_object_transformation_matrix[6];
    glm::mat4										m_skeleton_object_transformation_normal_matrix[6];
    glm::vec3										m_skeleton_object_position[6];
	glm::vec3										m_pirate_position;

    glm::vec3										m_explosion_position;

    class GeometryNode*								m_cannonball_object;
    glm::mat4										m_cannonball_object_transformation_matrix;
    glm::mat4                                       m_cannonball_object_transformation_normal_matrix;

    class GeometryNode*								m_menu_object;
    glm::mat4										m_menu_object_transformation_matrix;
    glm::mat4                                       m_menu_object_transformation_normal_matrix;

    class GeometryNode*								m_tower2_object;
    glm::mat4										m_tower2_object_transformation_matrix;
    glm::mat4                                       m_tower2_object_transformation_normal_matrix;

    class GeometryNode*								m_rocket_object;
    glm::mat4										m_rocket_object_transformation_matrix;
    glm::mat4                                       m_rocket_object_transformation_normal_matrix;

    class GeometryNode*								m_red_tile;

    class GeometryNode*								m_player_tile;

	std::vector<Tower>								m_towers;
    std::vector<Cannonball>							m_cannonballs;
    std::vector<Rocket> 							m_rockets;
	std::vector<Tile>								m_road;
	std::vector<Skeleton>							m_skeletons;
    std::vector<ParticleEmitter>                    m_particle_emitters;
    float                                           m_tower_shoot_timer;
    float                                           m_skeletons_wave_timer;
    float                                           m_new_tower_timer;
    float                                           m_particles_timer;
    int                                             m_level;
    bool                                            hit;
    int                                             exploded_cannonball_index;
    int                                             m_dead_skeletons;
    Skeleton                                        m_last_alive_skeleton;
    int                                             m_place_new_tower_time_limit;
    bool                                            m_default_tower;

    ParticleEmitter                                 m_particle_emitter;
    ShaderProgram                                   m_particle_rendering_program;

    class Chest*                                    chest;
    class Menu*                                     menu;

	// Protected Functions
	bool InitRenderingTechniques();
	bool InitDeferredShaderBuffers();
	bool InitCommonItems();
	bool InitLightSources();
	bool InitGeometricMeshes();

	void DrawGeometryNode(class GeometryNode* node, glm::mat4 model_matrix, glm::mat4 normal_matrix);
	void DrawGeometryNodeToShadowMap(class GeometryNode* node, glm::mat4 model_matrix, glm::mat4 normal_matrix);

	ShaderProgram								m_geometry_rendering_program;
	ShaderProgram								m_postprocess_program;
	ShaderProgram								m_spot_light_shadow_map_program;

public:
	Renderer();
	~Renderer();
	bool										Init(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	void										Update(float dt);
	bool										ResizeBuffers(int SCREEN_WIDTH, int SCREEN_HEIGHT);
	bool										ReloadShaders();
	void										Render();
    bool                                        GAME_OVER;

	// Passes
	void										RenderShadowMaps();
	void										RenderGeometry();
	void										RenderToOutFB();
	
	// Set functions
	void										SetRenderingMode(RENDERING_MODE mode);

	// Camera Function
	void										CameraMoveForward(bool enable);
	void										CameraMoveBackWard(bool enable);
	void										CameraMoveLeft(bool enable);
	void										CameraMoveRight(bool enable);
	void										CameraLook(glm::vec2 lookDir);
	void MovePlayer(int dx, int dz);

	void PlaceTower();

	bool isValidTowerPos();

	void MoveSkeleton(float dt);

    void PawnNewSkeletons(int level);

	void RemoveSkeleton();

    void RemoveTower();

    bool readRoad(const char *road);

    void shoot(float dt);

    void DrawText(const char *text, int length, int x, int y);

    void setDefaultTower(bool flag);

};

#endif
