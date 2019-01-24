#pragma once

#define SHOW_GRID

#include <memory>
#include <SDL.h>

#include "Core\RenderPackage\RenderPackage.h"
#include "Renderer\Objects\GLGrid.h"
#include "Sprites\SpriteRenderer.h"
#include "Textures\TextureContainer.h"
#include "Text\TextRenderer.h"

class GLRenderer
{
	public:
		GLRenderer(SDL_Window& window);

		void Draw(const RenderPackage& renderPackage);
		int GetMaxInstanceCount();

	private:
		SDL_Window& m_Window;
		SDL_GLContext m_GLContext;

        glm::mat4 m_VPMatrix_UI;

#ifdef SHOW_GRID
        std::unique_ptr<GLGrid> m_Grid_1;
        std::unique_ptr<GLGrid> m_Grid_5;
#endif
		std::unique_ptr<TextureContainer> m_TextureContainer;
		std::unique_ptr<SpriteRenderer> m_SpriteRenderer;	
        std::unique_ptr<TextRenderer> m_TextRenderer;
};