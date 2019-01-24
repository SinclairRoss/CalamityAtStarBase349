#include "Shader_BasicText.h"

std::string Shader_BasicText::VertexSource =
R"glsl(
        #version 330 core

        uniform mat4 u_ModelMatrices[MAX_INSTANCES];
        uniform vec2 u_UVCoords[MAX_INSTANCES];
        uniform vec2 u_GlyphTexSize[MAX_INSTANCES];
        uniform mat4 u_VPMatrix;

        in vec3 a_Vertex;
		in vec2 a_TexCoords;

        flat out int v_InstanceID;
		out vec2 v_TexCoords;

        void main()
        {
            vec2 uvBottomLeft = u_UVCoords[gl_InstanceID];
            vec2 glyphSize = u_GlyphTexSize[gl_InstanceID];
            vec2 uvTopRight = uvBottomLeft + glyphSize;

            v_InstanceID = gl_InstanceID;
			v_TexCoords = mix(uvBottomLeft, uvTopRight, a_TexCoords);

            mat4 m = u_ModelMatrices[gl_InstanceID];
            mat4 mvp = u_VPMatrix * m;
            gl_Position = mvp * vec4(a_Vertex, 1.0);
        }
    )glsl";

std::string Shader_BasicText::FragmentSource =
R"glsl(
        #version 330 core

		uniform sampler2D u_Texture;

        flat in int v_InstanceID;
		in vec2 v_TexCoords;

        out vec4 FragColour;

        void main()
        {
            FragColour = texture(u_Texture, v_TexCoords).rrrr * vec4(1, 1, 1, 1);
        }
    )glsl";