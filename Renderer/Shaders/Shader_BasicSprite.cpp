#include "Shader_BasicSprite.h"

std::string Shader_BasicSprite::VertexSource =
R"glsl(
        #version 330 core

        uniform mat4 u_ModelMatrices[MAX_INSTANCES];
        uniform mat4 u_VPMatrix;

        in vec3 a_Vertex;
		in vec2 a_TexCoords;

        flat out int v_InstanceID;
		out vec2 v_TexCoords;

        void main()
        {
            v_InstanceID = gl_InstanceID;
			v_TexCoords = a_TexCoords;

            mat4 m = u_ModelMatrices[gl_InstanceID];
            mat4 mvp = u_VPMatrix * m;
            gl_Position = mvp * vec4(a_Vertex, 1.0);
        }
    )glsl";

std::string Shader_BasicSprite::FragmentSource =
R"glsl(
        #version 330 core

        uniform vec4 u_Colour[MAX_INSTANCES];
		uniform sampler2D u_Texture[MAX_INSTANCES];

        flat in int v_InstanceID;
		in vec2 v_TexCoords;

        out vec4 FragColour;

        void main()
        {
            FragColour = texture(u_Texture[v_InstanceID], v_TexCoords) * u_Colour[v_InstanceID];
        }
    )glsl";
