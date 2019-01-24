#include "GLGrid.h"

#include <glm\gtc\type_ptr.hpp>

#include "Renderer\Shaders\Shader_Grid.h"
#include "Renderer\Helpers\ShaderHelpers.h"

#include "GameConstants\GameConstants.h"

#include <vector>

GLGrid::GLGrid(int width, int height, float scale) :
    m_TextureID(GameConstants::TextureData.GetIDWithName("Texture_Blank"))
{
    glGenVertexArrays(1, &m_VertexArrayObject);
    glBindVertexArray(m_VertexArrayObject);

    m_ShaderProgram = ShaderHelpers::CreateShader(Shader_Grid::VertexSource, Shader_Grid::FragmentSource);
    glUseProgram(m_ShaderProgram);

    int cells_X = width;
    int cells_Y = height;

    int numVertices_X = cells_X + 1;
    int numVertices_Y = cells_Y + 1;
    int numVertices = (numVertices_X * 2) + (numVertices_Y * 2);

    std::vector<GLfloat> vertices;
    vertices.reserve(numVertices * 5);

   for (int x = 0; x < numVertices_X; ++x)
   {
       float coord_X = static_cast<float>(x) * scale;
       float coord_Y = static_cast<float>(cells_Y) * scale;
       float coord_U = coord_X / cells_X;

       vertices.push_back(coord_X);
       vertices.push_back(0.0f);
       vertices.push_back(0.0f);
       vertices.push_back(coord_U);
       vertices.push_back(0.0f);

       vertices.push_back(coord_X);
       vertices.push_back(coord_Y);
       vertices.push_back(0.0f);
       vertices.push_back(coord_U);
       vertices.push_back(1.0f);
   }
   
   for (int y = 0; y < numVertices_Y; ++y)
   {
       float coord_X = static_cast<float>(cells_X) * scale;
       float coord_Y = static_cast<float>(y) * scale;
       float coord_V = coord_Y / cells_Y;
   
       vertices.push_back(0.0f);
       vertices.push_back(coord_Y);
       vertices.push_back(0.0f);
       vertices.push_back(0.0f);
       vertices.push_back(coord_Y / numVertices_Y);

       vertices.push_back(coord_X);
       vertices.push_back(coord_Y);
       vertices.push_back(0.0f);
       vertices.push_back(1.0f);
       vertices.push_back(coord_Y / numVertices_Y);
   }

    int numLines = numVertices_X + numVertices_Y;
    m_NumIndices = numLines * 2;

    std::vector<GLuint> indices;
    indices.reserve(m_NumIndices);

    for (int i = 0; i < numVertices; ++i)
    {
        indices.push_back(i);
    }

    indices.push_back(0);
    indices.push_back(cells_X * 2);
 
    indices.push_back(1);
    indices.push_back((cells_X * 2) + 1);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 5, vertices.data(), GL_STATIC_DRAW);

    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_NumIndices, indices.data(), GL_STATIC_DRAW);

    GLint vertexHandle = glGetAttribLocation(m_ShaderProgram, "a_Vertex");
    glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(vertexHandle);

    GLint texCoordHandle = glGetAttribLocation(m_ShaderProgram, "a_TexCoords");
    glVertexAttribPointer(texCoordHandle, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(texCoordHandle);

    m_VPMatrixHandle = glGetUniformLocation(m_ShaderProgram, "u_VPMatrix");
    m_TextureHandle = glGetUniformLocation(m_ShaderProgram, "u_Texture");
    m_ColourHandle = glGetUniformLocation(m_ShaderProgram, "u_Colour");
}

GLGrid::~GLGrid()
{}

void GLGrid::Draw(glm::mat4 &vpMatrix, const Colour& colour)
{
    glUseProgram(m_ShaderProgram);
    glBindVertexArray(m_VertexArrayObject);

    glUniformMatrix4fv(m_VPMatrixHandle, 1, GL_FALSE, glm::value_ptr(vpMatrix));
    glUniform1i(m_TextureHandle, m_TextureID);
    glUniform4f(m_ColourHandle, colour.R, colour.G, colour.B, colour.A);

    glDrawElements(GL_LINES, m_NumIndices, GL_UNSIGNED_INT, 0);
}