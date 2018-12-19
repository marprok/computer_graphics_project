#include <string>
#include <vector>
#include <unordered_map>
#include "GLEW\glew.h"

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

class ShaderProgram
{
	// filepaths of the shaders
	const char* vertexShaderFilename;
	const char* fragmentShaderFilename;
	
	// program and shaders
	GLuint program;
	GLuint vs, fs;

	// hash map with uniform indices
	std::unordered_map<std::string, GLint> uniforms;

public:
	ShaderProgram();
	~ShaderProgram();

	// Load Vertex and Fragment shader
	int LoadVertexShaderFromFile(const char* filename);
	int LoadFragmentShaderFromFile(const char* filename);
	
	// Create the program using the provided vertex and fragment shader
	bool CreateProgram();

	// Delete and reload shaders
	bool ReloadProgram();

	// Bind the program to use
	void Bind();
	// Unbind the program
	void Unbind();
	// Load the index of the uniform
	void LoadUniform(const std::string uniform);

	// Access the index of the uniform
	GLint operator[](const std::string key);
	GLint GetIndex(const std::string key);

private:
	// Create the shader
	bool CreateProgramShader();

	// Load the shader from the disk
	GLuint GenerateShader(const char* filename, GLenum shaderType);
	// print the log when something goes wrong
	void PrintLog(GLuint object);
};

#endif
