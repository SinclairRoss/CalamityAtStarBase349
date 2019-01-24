#pragma once

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <string>

namespace ShaderHelpers
{
	void SetMaxInstances(std::string& vertexSource, std::string& fragmentSource, int maxInstances);
    GLuint CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
    void CheckShader(GLuint shader);
};

