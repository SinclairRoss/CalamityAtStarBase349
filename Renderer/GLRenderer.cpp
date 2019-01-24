#include "GLRenderer.h"

#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>
#include <SDL_opengl.h>
#include <sstream>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Utils/ColourLibrary.h"

#include "GameConstants\GameConstants.h"
#include "Map\MapConstants.h"

#include "Helpers/ShaderHelpers.h"
#include "Shaders/Shader_BasicSprite.h"
#include "Shaders/Shader_BasicText.h"

GLRenderer::GLRenderer(SDL_Window& window) :
	m_Window(window),
	m_GLContext(SDL_GL_CreateContext(&m_Window)),
	m_TextureContainer(nullptr),
	m_SpriteRenderer(nullptr)
{
    if (m_GLContext != nullptr)
    {
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
        }

        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
            printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
        }

		// Calculate max number of instances. More to be done here.
		GLint numInstances = GetMaxInstanceCount();
		ShaderHelpers::SetMaxInstances(Shader_BasicSprite::VertexSource, Shader_BasicSprite::FragmentSource, numInstances);
		ShaderHelpers::SetMaxInstances(Shader_BasicText::VertexSource, Shader_BasicText::FragmentSource, numInstances);

        glClearColor(0.043137f, 0.0392156f, 0.0588235f, 1.0f);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);
		glDepthRangef(0.0f, 1.0f);
		glClearDepthf(1.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_TextureContainer = std::make_unique<TextureContainer>();
		m_SpriteRenderer = std::make_unique<SpriteRenderer>();
        m_TextRenderer = std::make_unique<TextRenderer>();

#ifdef SHOW_GRID
        int numCells_x = MapConstants::MapSize_x;
        int numCells_y = MapConstants::MapSize_y;
        m_Grid_1 = std::make_unique<GLGrid>(numCells_x, numCells_y, 1.0f);
        m_Grid_5 = std::make_unique<GLGrid>(numCells_x * 5, numCells_y * 5, 0.2f);
#endif
        glm::vec3 uiCamPos(0, 0, 1);
        glm::vec3 lookAtVec(0, 0, -1);
        glm::vec3 upVec(0, 1, 0);
        glm::mat4 viewMatrix = glm::lookAt(uiCamPos, lookAtVec, upVec);
        float ratio = GameConstants::Window.AspectRatio();
        glm::mat4 projectionMatrix = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.1f, 2.0f);
        m_VPMatrix_UI = projectionMatrix * viewMatrix;
	}
	else
	{
		printf("Warning: Unable to create OpenGL context! SDL Error: %s\n", SDL_GetError());
	}
}

void GLRenderer::Draw(const RenderPackage& renderPackage)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Camera& mainCamera = renderPackage.GetMainCamera();
    glm::mat4 vpMatrix = mainCamera.CalculateViewProjectionMatrix();

#ifdef SHOW_GRID
    m_Grid_1->Draw(vpMatrix, ColourLibrary::SexyOrange);
    m_Grid_5->Draw(vpMatrix, ColourLibrary::SexyOrange_Low);
#endif

    const RenderGroupContainer& rgc = renderPackage.GetRenderGroupContainer();
    rgc.ForeachRenderGroup([&](const RenderGroup_Sprites& rg)
    {
        m_SpriteRenderer->Draw(vpMatrix, rg);
    });

    const RenderGroup_Text& rgt = renderPackage.GetRenderGroupText();
    m_TextRenderer->Draw(m_VPMatrix_UI, rgt);

	SDL_GL_SwapWindow(&m_Window);
}

int GLRenderer::GetMaxInstanceCount()
{
	int numInstances;
	glGetIntegerv(GL_MAX_GEOMETRY_SHADER_INVOCATIONS, &numInstances);

	return numInstances;
}