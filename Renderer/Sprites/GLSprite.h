// name: Sprite
// date: 05/01/2017
// Note: A textured square.

#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

class GLSprite
{
    public:
	    GLSprite();

	    void Draw(const float transforms[], const int textures[], const float colours[], glm::mat4 &vpMatrix, const int numInstances);

    private:
	
	    unsigned int  m_VertexArrayObject;
	
	    GLuint m_ShaderProgram;

	    GLint m_ModelMatricesHandle;
        GLint m_TextureHandle;
        GLint m_ColourHandle;

	    GLint m_VPMatrixHandle;
};
