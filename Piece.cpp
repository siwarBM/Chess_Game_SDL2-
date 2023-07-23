#include "Piece.h"
#include "King.h"
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

std::vector<Piece::PossibleMove> Piece::pushMove(std::vector<PossibleMove> moveList,
																   PossibleMove move,
																   King* king,
																   Piece* field[8][8],
																   bool checkCheck)
{
	if (!checkCheck)
	{
		moveList.push_back(move);
	}
	else
	{
		bool enemyPlace = true;
		king->setCheck(field, king->getPos().first, king->getPos().second);
		Piece* zwisch = &(*field[move.xCoord][move.yCoord]);
		enemyPlace = false;

		if (field[move.xCoord][move.yCoord] != NULL)
		{
			enemyPlace = true;
			field[move.xCoord][move.yCoord] = NULL;
		}

		std::swap(field[move.xCoord][move.yCoord], field[m_pos.first][m_pos.second]);
		if (m_type == KING)
		{
			king->setCheck(field, move.xCoord, move.yCoord);
		}
		else
		{
			king->setCheck(field, king->getPos().first, king->getPos().second);
		}
		std::swap(field[move.xCoord][move.yCoord], field[m_pos.first][m_pos.second]);

		if (enemyPlace)
		{
			field[move.xCoord][move.yCoord] = &(*zwisch);
		}
		if (!king->getCheck())
		{
			moveList.push_back(move);
		}
		king->setCheck(field, king->getPos().first, king->getPos().second);
	}
	return moveList;
}

King* Piece::getOwnKing(Piece* field[8][8])
{
	for  (int i = 0; i < m_handler->PIECE_NUMBER; i++)
	{
		for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
		{
			if (field[i][j] != NULL)
			{
				if (field[i][j]->getTeam() == m_team && field[i][j]->getType() == Piece::KING)
				{
					King* ret = static_cast<King*>(field[i][j]);
					return ret;
				}
			}
		}
	}
	return NULL;
}

Piece::Piece(Team team, std::pair<int, int> pos, sdl_handler* handler, PieceType type)
	:m_team(team), m_pos(pos), m_handler(handler), m_texture(NULL), m_hasMoved(false), m_type(type)
{
}

Piece::Piece(const Piece& piece)
	:m_team(piece.m_team), m_pos(piece.m_pos), m_handler(piece.m_handler), m_texture(NULL), m_hasMoved(false), m_type(piece.m_type)
{
}

Piece::~Piece()
{
	SDL_DestroyTexture(m_texture);

	m_handler->undoPieceRender(m_pos.first, m_pos.second);
}


void Piece::render()
{
	SDL_Rect src = {0, 0, 60, 60};
	if (m_handler == NULL)
	{
		assert(m_handler != NULL);
	}
	SDL_Rect dest = { m_handler->SCREEN_WIDTH / m_handler->PIECE_NUMBER * m_pos.first - 2,
					  m_handler->SCREEN_HEIGHT / m_handler->PIECE_NUMBER * m_pos.second,
					  m_handler->SCREEN_WIDTH / m_handler->PIECE_NUMBER,
					  m_handler->SCREEN_HEIGHT / m_handler->PIECE_NUMBER };
	m_handler->DrawRectangle(src, dest, m_texture);
}