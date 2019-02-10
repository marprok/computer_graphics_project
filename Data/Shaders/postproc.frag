#version 330
layout(location = 0) out vec4 out_color;

uniform sampler2D uniform_texture;
uniform sampler2D uniform_depth;
uniform float uniform_time;
uniform mat4 uniform_projection_inverse_matrix;

uniform int game_over;
uniform int place_mode;

uniform int blue_towers;
uniform int red_towers;
uniform int coins_left;

uniform int lose_coins_effect;

in vec2 f_texcoord;

#define DOF_RADIUS 4
#define BLOOM_RADIUS 3

#define PI 3.14159

float gaussian(vec2 uv)
{
	const float sigma = 6;
	const float sigma2 = 2 * sigma * sigma;
	
	return 4*exp(-dot(uv,uv) / sigma2) / (PI * sigma2);
}

float gaussian(vec2 uv, float sigma)
{
	float sigma2 = 2 * sigma * sigma;
	
	return 4*exp(-dot(uv,uv) / sigma2) / (PI * sigma2);
}

void main(void)
{
	
	vec3 color = texture(uniform_texture, f_texcoord).rgb;
	vec2 uv = f_texcoord;
	
//#define BLOOM
#ifdef BLOOM
	
	vec2 texSize = textureSize(uniform_texture, 0);
	
	// check each corner
	for(int x = -BLOOM_RADIUS; x <= BLOOM_RADIUS; ++x)
	{
		for(int y = -BLOOM_RADIUS; y <= BLOOM_RADIUS; ++y)
		{
			vec3 color2 = texture(uniform_texture, f_texcoord + 2 * vec2(x,y) / texSize).rgb;
			float lum = dot(vec3(0.30, 0.59, 0.11), color2);
			if(lum > 1.0)
				color += 1.2*gaussian(vec2(x,y)) * color2;
		}
	}
#endif	

//#define BLOOM2
#ifdef BLOOM2

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);
	
	vec2 texSize = textureSize(uniform_texture, 0);
	
	float my_radius = 4;
	
	for(int i=0;i<16;i++)
	{
		vec3 color2 = texture(uniform_texture, f_texcoord + my_radius * poissonDisk[i] / texSize).rgb;
		float lum = dot(vec3(0.30, 0.59, 0.11), color2);
		if(lum > 1.0)
			color += 1.2*gaussian(poissonDisk[i],3) * color2;
	}
		
#endif	

// DEPTH BUFFER PREVIEW
// HERE we will make the Depth Buffer Visible
//#define VISUALIZE_DEPTH_BUFFER
#ifdef VISUALIZE_DEPTH_BUFFER
	// get the value of the depth buffer
	float depth = texture(uniform_depth, f_texcoord.xy).r;
	vec4 pos = vec4(f_texcoord, depth, 1);
	pos.xyz = 2 * pos.xyz - 1;
	pos = uniform_projection_inverse_matrix * pos;
	pos /= pos.w;
	
	// convert it to a positive number
	float z_coord = -pos.z;
	
	// scale down to make it visible
	z_coord *= 0.05;
	
	color = vec3(z_coord);
#endif

//#define DOF
#ifdef DOF

	// get the value of the depth buffer
	float depth = texture(uniform_depth, f_texcoord.xy).r;
	vec4 pos = vec4(f_texcoord, depth, 1);
	pos.xyz = 2 * pos.xyz - 1;
	pos = uniform_projection_inverse_matrix * pos;
	pos /= pos.w;
	
	// convert it to a positive number
	float z_coord = -pos.z;
	
	float focus = 6.2; // focus distance
	const float blurclamp = 2.0; // max blur amount
	const float focalRange = 4; // focus range
	
	float factor = abs(z_coord - focus) / focalRange;
	// clamp the blur intensity
	vec2 dofblur = vec2 (clamp( factor, 0, blurclamp ));
	
	// get the size of the intermediate texture
	vec2 texSize = textureSize(uniform_texture, 0);
	
	float sum = 0.0;
	
	// clear the color value
	color = vec3(0);
	
	// check each corner
	for(int x = -DOF_RADIUS; x <= DOF_RADIUS; ++x)
	{
		for(int y = -DOF_RADIUS; y <= DOF_RADIUS; ++y)
		{
			vec2 offset = 2.25 * vec2(x,y);
			vec3 color2 = texture(uniform_texture, f_texcoord + dofblur * offset / texSize).rgb;
			
			float weight_value = gaussian(offset);
			color += weight_value * color2;
			sum += weight_value;
		}
	}
	color /= sum;

#endif
	
	if (lose_coins_effect == 1) {
		vec2 pos2 = uv - vec2(0.5, 0.5);
		float dist2 = sqrt(pos2.x * pos2.x + pos2.y * pos2.y);
		float max_dist = sqrt(0.5);
		float min_dist = sqrt(0.1);
		if (dist2 > min_dist) {
			color += ((dist2 - min_dist) / max_dist) * vec3(0.3, 0, 0);
		}
	}
	
	if (game_over == 1) {
		
		// grayscale
		color = vec3(color.r + color.g + color.b) / 3.0;
		
		vec2 pos3 = uv - vec2(0.5, 0.5);
		float dist3 = sqrt(pos3.x * pos3.x + pos3.y * pos3.y);
		float mask = 1.0 - dist3 * 1.5;
		color = color * mask;
	
	} else {

		float start_x	=	0.025;
		float start_y	=	0.02;
		
		float width		=	0.02;
		float height	=	0.02;
		
		float offset	=	0.005;
		
		float radius = height / 2.5;
		vec2 center;
		center.x = start_x / 2;


		vec2 pos;
		
		int number_of_loops = coins_left / 10;
		center.y = 1 - start_y;
		center.x = start_x;
		float dist;
		for (int i=0; i<number_of_loops; i++)
		{
			pos = uv - center;
			dist = sqrt(pos.x * pos.x + pos.y * pos.y);
			if (dist < radius) 
			{
				color = vec3(0.92f, 0.83f, 0.f);
			}
			center.x += offset + 2*radius;
		}

		// draw container
		start_x			=	0.003;
		start_y			=	0.01;
		
		width			=	0.173;
		height			=	0.07;
		
		float shadow_x	=	0.0025;
		float shadow_y	=	0.0025;
		
		if ((uv.x > start_x - shadow_x) && (uv.x < start_x + width + shadow_x) && (uv.y > start_y - shadow_y) && (uv.y < start_y + height + shadow_y)) {
			color = vec3(0.4);
		}
		
		if ((uv.x > start_x) && (uv.x < start_x + width) && (uv.y > start_y) && (uv.y < start_y + height)) {
			color = vec3(0.5);
		}
		
		// loading rectangles dimensions
		float x_offset	=	0.005;
		float y_offset	=	0.01;
		
		start_x			=	0.025;
		start_y			=	0.02;
		
		width			=	0.02;
		height			=	(height - 3 * y_offset) / 2;
		
		// draw blue rectangles
		float x_start_blue = start_x;
		float y_start_blue = start_y;
		
		for (int i = 0; i < blue_towers; i++) {
			if ((uv.x > x_start_blue) && (uv.x < x_start_blue + width) && (uv.y > y_start_blue) && (uv.y < y_start_blue + height)) {
				color = vec3(0, 0, 1);
			}
			x_start_blue += width + x_offset;
		}
		
		// draw red rectangles
		float x_start_red = start_x;
		float y_start_red = start_y;
		
		y_start_red += height + y_offset;
		
		for (int i = 0; i < red_towers; i++) {
			if ((uv.x > x_start_red) && (uv.x < x_start_red + width) && (uv.y > y_start_red) && (uv.y < y_start_red + height)) {
				color = vec3(1, 0, 0);
			}
			x_start_red += width + x_offset;
		}
		
		// draw the selection circle
		radius = height / 2.5;
		
		center.x = start_x / 2;
		
		if (place_mode == 1) {
			center.y = y_start_blue;
		} else {
			center.y = y_start_red;
		}
		
		center.y += height / 2;
		
		pos = uv - center;
		dist = sqrt(pos.x * pos.x + pos.y * pos.y);
		if (dist < radius) {
			color = vec3(0);
		}
		
	}
	
	out_color = vec4(color, 1.0);

}
