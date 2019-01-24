#include "GLSprite.h"

#include <glm\gtc\type_ptr.hpp>

#include "Renderer\Helpers\ShaderHelpers.h"
#include "Renderer\Shaders\Shader_BasicSprite.h"

GLSprite::GLSprite()
{
	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	m_ShaderProgram = ShaderHelpers::CreateShader(Shader_BasicSprite::VertexSource, Shader_BasicSprite::FragmentSource);
	glUseProgram(m_ShaderProgram);

	const float size = 0.5f;

	// x, y, z, u, v 
	const GLfloat vertices[] =
	{
		  size,  size, 0.0f,	1.0f,  1.0f,
		 -size,  size, 0.0f,	0.0f,  1.0f,
		  size, -size, 0.0f,	1.0f,  0.0f,
		 -size, -size, 0.0f,	0.0f,  0.0f
	};

	const GLuint indices[] =
	{ 
		0, 1, 2,
		1, 3, 2
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint vertexHandle = glGetAttribLocation(m_ShaderProgram, "a_Vertex");
	glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(vertexHandle);

	GLint texCoordHandle = glGetAttribLocation(m_ShaderProgram, "a_TexCoords");
	glVertexAttribPointer(texCoordHandle, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(texCoordHandle);

	m_ModelMatricesHandle = glGetUniformLocation(m_ShaderProgram, "u_ModelMatrices");
	m_ColourHandle = glGetUniformLocation(m_ShaderProgram, "u_Colour");
    m_TextureHandle = glGetUniformLocation(m_ShaderProgram, "u_Texture");
	m_VPMatrixHandle = glGetUniformLocation(m_ShaderProgram, "u_VPMatrix");
}

void GLSprite::Draw(const float transforms[], const int textures[], const float colours[], glm::mat4 &vpMatrix, const int numInstances)
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VertexArrayObject);

	glUniformMatrix4fv(m_ModelMatricesHandle, numInstances, GL_FALSE, transforms);
	glUniformMatrix4fv(m_VPMatrixHandle, 1, GL_FALSE, glm::value_ptr(vpMatrix));
    glUniform1iv(m_TextureHandle, numInstances, textures);
    glUniform4fv(m_ColourHandle, numInstances, colours);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, numInstances);
}

