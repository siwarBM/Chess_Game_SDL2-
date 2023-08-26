#include "Knight.h"
#include <iostream>

Knight::Knight(Team team, std::pair<int, int> pos, sdl_handler* handler)
	:Piece(team, pos, handler, KNIGHT)
{
	std::string imagename;
	imagename = (team == BLACK) ? "img/Chess_ndt60.png" : "img/Chess_nlt60.png";
	m_handler = handler;
	m_texture = handler->loadImage(imagename);
	render();
}

void Knight::sayMyName()
{
	std::string msg = (m_team == BLACK) ? "BLACK KNIGHT" : "WHTIE KNIGHT";

	std::cout << msg << std::endl;
}

void Knight::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<Piece::PossibleMove> moves;
	
	for (int dx = -2; dx <= 2 ; dx += 4)
	{
		for (int dy = -1; dy <= 1; dy += 2)
		{
			if (m_pos.first + dx >= 0 && m_pos.first + dx <= 7 && m_pos.second + dy >= 0 && m_pos.second + dy <= 7)
			{
				if (field[m_pos.first + dx][m_pos.second + dy] == nullptr)
				{
					struct PossibleMove p1 = {m_pos.first + dx, m_pos.second + dy, Piece::NORMAL};
					moves = pushMove(moves,
									 p1,
									 getOwnKing(field),
									 field,
									 checkCheck);
				}
				else if (field[m_pos.first + dx][m_pos.second + dy] != nullptr)
				{
					if (field[m_pos.first + dx][m_pos.second + dy]->getTeam() != m_team)
					{
						struct PossibleMove p1 = {m_pos.first + dx, m_pos.second + dy, Piece::NORMAL};
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

	for (int dy = -2; dy <= 2; dy += 4)
	{
		for (int dx = -1; dx <= 1; dx += 2)
		{
			if (m_pos.first + dx >= 0 && m_pos.first + dx <= 7 && m_pos.second + dy >= 0 && m_pos.second + dy <= 7)
			{
				if (field[m_pos.first + dx][m_pos.second + dy] == nullptr)
				{
					struct PossibleMove p1 = {m_pos.first + dx, m_pos.second + dy, Piece::NORMAL};
					moves = pushMove(moves,
						p1,
						getOwnKing(field),
						field,
						checkCheck);
				}
				else if (field[m_pos.first + dx][m_pos.second + dy] != nullptr)
				{
					if (field[m_pos.first + dx][m_pos.second + dy]->getTeam() != m_team)
					{
						struct PossibleMove p1 = {m_pos.first + dx, m_pos.second + dy, Piece::NORMAL};
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