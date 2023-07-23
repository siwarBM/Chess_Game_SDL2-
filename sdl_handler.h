#ifndef SDL_HANDLER_H // Replace PIECE_H with a unique identifier for each header file
#define SDL_HANDLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class sdl_handler
{
private:
    /* data */
public:
    sdl_handler(/* args */);
    	// Screen size
	const int SCREEN_WIDTH = 480;
	const int SCREEN_HEIGHT = 480;
	const int CELL_WIDTH = SCREEN_WIDTH / 8;
	const int PIECE_NUMBER = 8;

	// window we'll be rendering to
	SDL_Window* m_window;

	// Surface contained by the window
	SDL_Surface* m_screenSurface;

	// Renderer
	SDL_Renderer* m_renderer;

	// Event (Mouseclick etc)
	SDL_Event m_event;
	
	// initialize the field
	// returns true, if everything worked
	bool init();

	// renders the source rectangle of the texture to dest rectangle
	void DrawRectangle(SDL_Rect source, SDL_Rect dest, SDL_Texture* text);

	// removes PieceRender
	void undoPieceRender(int x, int y);

	// gets filename, return texture of the jpg file
	SDL_Texture* loadImage(std::string filename);

	//renders the background of the field
	void renderBackground();

    // cleans up SDL stuff
	void cleanUp();

    // Destructor
    ~sdl_handler();
};
#endif