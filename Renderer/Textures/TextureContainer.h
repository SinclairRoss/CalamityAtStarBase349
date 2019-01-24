// name: TextureContainer
// date: 05/01/2017
// Note: Loads and stores every texture used.

#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include <string>
#include <vector>

class TextureContainer
{
	public:
		TextureContainer();
		~TextureContainer();

	private:
		GLuint LoadTexture(const std::string& path, int textureIndex, int textureFormat);

        std::vector<GLuint> m_TextureHandles;
};
