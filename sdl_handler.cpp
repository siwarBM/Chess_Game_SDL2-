#include "sdl_handler.h"

#include <stdio.h>
#include <iostream>


void sdl_handler::renderBackground()
{
	bool white = true;
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	for (int i = 0; i < PIECE_NUMBER; i++)
	{
		for (int j = 0; j < PIECE_NUMBER; j++)
		{
			if (white)
			{
				SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
			}
			else
			{
				/*SDL_SetRenderDrawColor(m_renderer, 155, 103, 60, 255);*/
				SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);

			}
			white = !white;
			SDL_Rect rectangle = { i * SCREEN_WIDTH / PIECE_NUMBER,
								  j * SCREEN_HEIGHT / PIECE_NUMBER,
								  SCREEN_WIDTH / PIECE_NUMBER,
								  SCREEN_HEIGHT / PIECE_NUMBER };
			SDL_RenderFillRect(m_renderer, &rectangle);
		}
		white = !white;
	}
}

SDL_Texture* sdl_handler::loadImage(std::string imagename)
{
	SDL_Surface* loadedImage = NULL;

	loadedImage = IMG_Load(imagename.c_str());

	if (loadedImage == NULL)
	{
		std::cout << "could'nt load Image" << imagename << std::endl;
	}

	SDL_Texture* text = SDL_CreateTextureFromSurface(m_renderer, loadedImage);

	return text;
}

void sdl_handler::undoPieceRender(int x, int y)
{
	if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	}
	else
	{
		//SDL_SetRenderDrawColor(m_renderer, 155, 103, 60, 255);
		SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	}
	SDL_Rect rectangle = { x * SCREEN_WIDTH / PIECE_NUMBER,
						  y * SCREEN_HEIGHT / PIECE_NUMBER,
						  SCREEN_WIDTH / PIECE_NUMBER,
						  SCREEN_HEIGHT / PIECE_NUMBER };
	SDL_RenderFillRect(m_renderer, &rectangle);
}

void sdl_handler::cleanUp()
{
	SDL_FreeSurface(m_screenSurface);
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}


void sdl_handler::DrawRectangle(SDL_Rect source, SDL_Rect dest, SDL_Texture* text)
{
	if (text != NULL)
	{
		SDL_RenderCopy(m_renderer, text, &source, &dest);
		SDL_RenderPresent(m_renderer);

		SDL_UpdateWindowSurface(m_window);
	}
	else
	{
		std::cout << "DrawRectangle: text was nullptr" << std::endl;
	}
}

sdl_handler::~sdl_handler()
{
}
sdl_handler::sdl_handler()
{

}

bool sdl_handler::init()
{
	m_window = NULL;
	m_screenSurface = NULL;

	//bool quit = false;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		cleanUp();
		return false;
	}
	else
	{
		//Create window
		m_window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		}
	}
	return true;
}
