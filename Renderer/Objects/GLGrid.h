#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include "Core\Utils\Colour.h"

class GLGrid
{
    public:
        GLGrid(int width, int height, float scale);
        ~GLGrid();

        void Draw(glm::mat4 &vpMatrix, const Colour& colour);

    private:

        unsigned int  m_VertexArrayObject;
        int m_NumIndices;

        GLuint m_ShaderProgram;
        GLint m_VPMatrixHandle;
        GLint m_TextureHandle;
        GLint m_ColourHandle;

        int m_TextureID;
};
