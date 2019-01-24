#include <SDL.h>
#include <SDL_mixer.h>
#include <sstream>
#include <cstdlib>
#include <time.h>

#include "GameConstants\GameConstants.h"
#include "Core\GameShell\GameShell.h"

void InitialiseEnvironment(SDL_Window** window);
void CleanEnvironment(SDL_Window* window);

int main(int, char* [])
{
	SDL_Window* window = nullptr;
	InitialiseEnvironment(&window);

    srand(static_cast<unsigned int>(time(NULL)));

	GameShell gameShell(*window);	
	gameShell.RunGame();

	CleanEnvironment(window);

	return 1;
}

void InitialiseEnvironment(SDL_Window** window)
{
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
	if (result >= 0)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        int screenWidth = GameConstants::Window.ScreenWidth();
        int screenHeight = GameConstants::Window.ScreenHeight();
        int windowMode = GameConstants::Window.WindowMode();

		*window = SDL_CreateWindow("Calamity at Starbase:349", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | windowMode | SDL_WINDOW_SHOWN);
		if (*window == nullptr)
		{
			printf("SDL could not create window! SDL_Error: %s\n", SDL_GetError());
		}
	}
	else
	{
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
	}
}

void CleanEnvironment(SDL_Window* window)
{
	SDL_DestroyWindow(window);
}