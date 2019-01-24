#include "Shader_Grid.h"

std::string Shader_Grid::VertexSource =
R"glsl(
        #version 330 core

        uniform mat4 u_VPMatrix;

        in vec3 a_Vertex;
        in vec2 a_TexCoords;

        out vec2 v_TexCoords;

        void main()
        {
            v_TexCoords = a_TexCoords;
            gl_Position = u_VPMatrix * vec4(a_Vertex, 1.0);
        }
    )glsl";

std::string Shader_Grid::FragmentSource =
R"glsl(
        #version 330 core

        uniform sampler2D u_Texture;
        uniform vec4 u_Colour;

        in vec2 v_TexCoords;

        out vec4 FragColour;

        void main()
        {
            FragColour = texture(u_Texture, v_TexCoords) * u_Colour;
        }
    )glsl";