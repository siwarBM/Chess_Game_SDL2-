#include <SDL.h>
#include <stdio.h>
#include "mainLoop.h"
#include "sdl_handler.h"
#include "Game.h"
#include <iostream>

#include <memory>

void mainloop::run()
{  std::cout << "start run dunction" <<std::endl;
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
                xStart = handler->m_event.button.x / 80;
				yStart = handler->m_event.button.y / 80;
				clickedOn = game->getFieldPos(xStart, yStart);
				if (clickedOn != NULL)
				{
					if (clickedOn->getTeam() == game->getTurn())
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
					if (clickedOn->getTeam() == game->getTurn())
					{
						game->undoRenderPossibleMoves(clickedOn);
					}
				}
				xEnd = handler->m_event.button.x / 80;
				yEnd = handler->m_event.button.y / 80;
				if (clickedOn != NULL)
				{
					if ((xStart != -1 && yStart != -1 && xEnd != -1 && yEnd != -1)
						&& (clickedOn->getTeam() == game->getTurn())
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

                                // Create a vector and add the PossibleMove object
                                //std::vector<Piece::PossibleMove> p1 = {move};
								//std::vector<Piece::PossibleMove> p1 ={xEnd,yEnd,value.moveType};
								//{xEnd, yEnd, value.moveType};
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
	//handler->cleanUp();
}