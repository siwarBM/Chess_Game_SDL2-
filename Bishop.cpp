#include "Bishop.h"
#include <iostream>

Bishop::Bishop(Team team, std::pair<int, int> pos, sdl_handler* handler) : Piece(team, pos, handler, BISHOP)
{
	std::string imagename;

	imagename = (team == BLACK ) ? "img/Chess_bdt60.png" : "img/Chess_blt60.png";
	m_handler = handler;
	m_texture = handler->loadImage(imagename);
	render();
}

void Bishop::sayMyName()
{
	std::string msg = (m_team == BLACK ) ? "BLACK BISHOP" : "WHTIE BISHOP";
	std::cout << msg << std::endl;
}

struct PossibleMove
{
	    int xCoord, yCoord;
        Piece::MoveType MoveType;
};

void Bishop::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<PossibleMove> moves;
	int dx_copy;
	int dy_copy;
	for (int dx = -1; dx <= 1; dx += 2)
	{
		for (int dy = -1; dy <= 1; dy += 2)
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
				dx_copy = (dx_copy < 0 ) ? dx_copy -= 1 : dx_copy+=1;
				dy_copy = (dy_copy < 0 ) ? dy_copy -= 1 : dy_copy+=1;
			}
			if (field[m_pos.first + dx_copy][m_pos.second + dy_copy] != nullptr
				&& (m_pos.first + dx_copy >= 0 && m_pos.first + dx_copy <= 7 && m_pos.second + dy_copy >= 0 && m_pos.second + dy_copy <= 7))
			{
				if (field[m_pos.first + dx_copy][m_pos.second + dy_copy]->getTeam() != m_team)
				{
					struct PossibleMove p1 = {m_pos.first + dx_copy, m_pos.second + dy_copy, Piece::NORMAL};
					moves = pushMove(moves,
						p1,
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	} 

	m_possibleMoves = moves;
}



