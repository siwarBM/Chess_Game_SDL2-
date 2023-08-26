#include <SDL.h>
#include <stdio.h>
#include "mainLoop.h"
#include "sdl_handler.h"
#include "Game.h"
#include "Piece.h"
#include <iostream>

#include <memory>

bool mainloop::isvalidmove(Piece* clickedOn, Game* game)
{
	if (clickedOn != NULL)
	{
		if (clickedOn->getTeam() == game->getTurn())
		{
			return true;

		}
	}
	return false;
}

void mainloop::run()
{
	sdl_handler* handler = new sdl_handler();
	handler->init();

	handler->renderBackground();
	
	Game* game = new Game(handler);

	bool quit = false;

	int xStart = -1;
	int yStart = -1;
	int xEnd = -1;
	int yEnd = -1;
	Piece* clickedOn = NULL;

	while ( ! quit )
	{
		while (SDL_WaitEvent(&handler->m_event)) // Check the role of SDL_WaitEvent"ént here added by me.
		{
            switch (handler->m_event.type)
            {
            case SDL_QUIT:/* constant-expression */{
                                /* code */
                quit = true;
                break;

            }
            case SDL_MOUSEBUTTONDOWN:
            {
                xStart = handler->m_event.button.x / handler->CELL_WIDTH;
				yStart = handler->m_event.button.y / handler->CELL_WIDTH;
				clickedOn = game->getFieldPos(xStart, yStart);
				if (clickedOn != NULL)
				{
					if ( isvalidmove(clickedOn,game) )
					{
						game->renderPossibleMoves(clickedOn);
					}
				}
                break;

            }
            case SDL_MOUSEBUTTONUP :
            {

                if (clickedOn != NULL)
				{
					if ( isvalidmove(clickedOn,game) )
					{
						// Used to refresh the application.
						game->undoRenderPossibleMoves(clickedOn);
					}
				}
				xEnd = handler->m_event.button.x / handler->CELL_WIDTH;
				yEnd = handler->m_event.button.y / handler->CELL_WIDTH;
				if (clickedOn != NULL)
				{
					if ((xStart != -1 && yStart != -1 && xEnd != -1 && yEnd != -1)
						&& ( isvalidmove(clickedOn,game) )
						&& (game->isValidMove(xEnd, yEnd, clickedOn)))
					{
						std::vector<Piece::PossibleMove> list = game->getFieldPos(xStart, yStart)->getPossibleMoves();
						for (const auto& value : list)
						{
							if (value.xCoord == xEnd && value.yCoord == yEnd)
							{
								// Construct a Piece::PossibleMove object
                                Piece::PossibleMove move;
                                move.xCoord = xEnd;
                                move.yCoord = yEnd;
                                move.moveType = value.moveType;
								game->move(clickedOn, move);

							}
						}
						xStart = -1;
						yStart = -1;
						yEnd = -1;
						game->calcAllMoves();
						clickedOn = nullptr;
					}
                }
                break;
            }
            default:
                break;
            }
		}
	}
    delete handler;
	delete game;
}