#include "Rook.h"
#include <iostream>

Rook::Rook(Team team, std::pair<int, int> pos, sdl_handler* handler)
	:Piece(team, pos, handler, ROOK)
{
	std::string imagename = (team == BLACK) ? "img/Chess_rdt60.png" : "img/Chess_rlt60.png";
	m_handler = handler;
	m_texture = handler->loadImage(imagename);

	render();
}

void Rook::sayMyName()
{
	std::string msg = (m_team == BLACK) ? "BLACK ROOK" : "WHITE ROOK";
	std::cout << msg << std::endl;
}

void Rook::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<PossibleMove> moves;

	int dx_copy;
	int dy_copy;
	for (int dx = -1; dx <= 1; dx ++)
	{
		for (int dy = -1; dy <= 1; dy ++)
		{
			if (dy == 0 || dx == 0)
			{
				dx_copy = dx;
				dy_copy = dy;
				while (field[m_pos.first + dx_copy][m_pos.second + dy_copy] == NULL
					&& (m_pos.first + dx_copy >= 0 && m_pos.first + dx_copy <= 7 && m_pos.second + dy_copy >= 0 && m_pos.second + dy_copy <= 7))
				{
					struct PossibleMove p1 = { m_pos.first + dx_copy, m_pos.second + dy_copy, Piece::NORMAL };
					moves = pushMove(moves,
									 p1,
									 getOwnKing(field),
									 field,
									 checkCheck);

					if (dx_copy < 0)
					{
						dx_copy -= 1;
					}
					else if (dx_copy > 0)
					{
						dx_copy += 1;
					}
					if (dy_copy < 0)
					{
						dy_copy -= 1;
					}
					else if (dy_copy > 0)
					{
						dy_copy += 1;
					}
				}
				if (field[m_pos.first + dx_copy][m_pos.second + dy_copy] != NULL
					&& (m_pos.first + dx_copy >= 0 && m_pos.first + dx_copy <= 7 && m_pos.second + dy_copy >= 0 && m_pos.second + dy_copy <= 7))
				{
					if (field[m_pos.first + dx_copy][m_pos.second + dy_copy]->getTeam() != m_team)
					{
						struct PossibleMove p1 = { m_pos.first + dx_copy, m_pos.second + dy_copy, Piece::NORMAL };
						moves = pushMove(moves,
										 p1,
										 getOwnKing(field),
										 field,
										 checkCheck);
					}
				}
			}
		}
	}

	m_possibleMoves = moves;
}


Rook::~Rook()
{
}
