//
// Created by Mad Beast on 14/09/2017.
//

#include "ShaderHelpers.h"

#include <sstream>
#include <string>

void ShaderHelpers::SetMaxInstances(std::string& vertexSource, std::string& fragmentSource, int maxInstances)
{
	std::string placeholder("MAX_INSTANCES");
	std::string str_instances = std::to_string(maxInstances);

	size_t pos = vertexSource.find(placeholder, 0);
	while (pos != vertexSource.npos)
	{
		vertexSource.replace(pos, placeholder.length(), str_instances);
		pos = vertexSource.find(placeholder, 0);
	} 

	pos = fragmentSource.find(placeholder, 0);
	while (pos != fragmentSource.npos)
	{
		fragmentSource.replace(pos, placeholder.length(), str_instances);
		pos = fragmentSource.find(placeholder, 0);
	}
}

GLuint ShaderHelpers::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* cstr_vertex = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &cstr_vertex, nullptr);
    glCompileShader(vertexShader);
    ShaderHelpers::CheckShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* cstr_fragment = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &cstr_fragment, nullptr);
    glCompileShader(fragmentShader);
    ShaderHelpers::CheckShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    return shaderProgram;
}

void ShaderHelpers::CheckShader(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, nullptr, buffer);

		printf("Shader Compilation Error: \n %s", buffer);
    }
}