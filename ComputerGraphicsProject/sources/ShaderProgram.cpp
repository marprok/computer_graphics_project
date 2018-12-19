#include "../headers/ShaderProgram.h"
#include "../headers/Tools.h"
#include "SDL2\SDL.h"

ShaderProgram::ShaderProgram()
{
	program = 0;

	vertexShaderFilename = NULL;
	fragmentShaderFilename = NULL;
	vs = 0;
	fs = 0;
}

ShaderProgram::~ShaderProgram()
{
	delete[] vertexShaderFilename;
	delete[] fragmentShaderFilename;
	glDeleteProgram(program);
}

int ShaderProgram::LoadVertexShaderFromFile(const char* filename)
{
	// copy vertex shader file path
	char* fname = new char[strlen(filename) + 1];
	strcpy(fname, filename);
	vertexShaderFilename = fname;
	return 0;
}
int ShaderProgram::LoadFragmentShaderFromFile(const char* filename)
{
	// copy fragment shader file path
	char* fname = new char[strlen(filename) + 1];
	strcpy(fname, filename);
	fragmentShaderFilename = fname;
	return 0;
}

bool ShaderProgram::CreateProgramShader()
{
	glDeleteProgram(program);
	program = glCreateProgram();
	// load the VS Shader
	if ((vs = GenerateShader(vertexShaderFilename, GL_VERTEX_SHADER)) == 0) return false;
	glAttachShader(program, vs);
	//glDeleteShader(vs);


	// load the FS shader
	if ((fs = GenerateShader(fragmentShaderFilename, GL_FRAGMENT_SHADER)) == 0) return false;
	glAttachShader(program, fs);
	//glDeleteShader(fs);

	// link them
	GLint link_ok = GL_FALSE;
	GLint validate_ok = GL_FALSE;
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		printf("glLinkProgram:");
		PrintLog(program);
		return false;
	}
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_ok);
	if (!validate_ok) {
		printf("glValidateProgram:");
		PrintLog(program);
		return false;
	}
	return true;
}

bool ShaderProgram::CreateProgram()
{
	// if fail, show text message and redo
	SDL_assert_release(CreateProgramShader());
	return true;
}

void ShaderProgram::LoadUniform(std::string uniform)
{
	uniforms[uniform] = glGetUniformLocation(program, uniform.c_str());
}

bool ShaderProgram::ReloadProgram()
{
	SDL_assert_release(CreateProgramShader());
	for (auto& it : uniforms)
	{
		it.second = glGetUniformLocation(program, it.first.c_str());
	}
	return true;
}

void ShaderProgram::Bind()
{
	glUseProgram(program);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0);
}

void ShaderProgram::PrintLog(GLuint object)
{
	GLint log_length = 0;
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else 
	{
		printf("printlog: Not a shader or a program\n");
		return;
	}

	char* log = new char[log_length];

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);

	printf("%s", log);
	delete[] log;
}

GLuint ShaderProgram::GenerateShader(const char* filename, GLenum shaderType)
{
	const char* source = Tools::LoadWholeStringFile(filename);
	if (source == NULL) {
		printf("Error opening %s: ", filename);
		delete[] source;
		return 0;
	}
	
	GLuint res = glCreateShader(shaderType);

	glShaderSource(res, 1, &source, NULL);
	delete[] source;

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		printf("%s:", filename);
		PrintLog(res);
		glDeleteShader(res);
		return 0;
	}

	return res;
}

GLint ShaderProgram::operator[](const std::string key)
{
	auto it = uniforms.find(key);
	return (it != uniforms.end()) ? it->second : -1;
}

GLint ShaderProgram::GetIndex(const std::string key)
{
	auto it = uniforms.find(key);
	return (it != uniforms.end()) ? it->second : -1;
}
