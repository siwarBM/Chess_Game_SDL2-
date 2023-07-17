#pragma once
#include "Pawn.h"
#include <iostream>
#include <list>

Pawn::Pawn(Team team, std::pair<int, int> pos, sdl_handler* handler)
	:Piece(team, pos, handler, PAWN), m_enPassant(std::pair<bool, int>(false, 0))
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "res/Chess_pdt60.png";
	}
	else
	{
		filename = "res/Chess_plt60.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	if (team == BLACK)
	{
		m_dy = -1;
	}
	else
	{
		m_dy = 1;
	}

	render();
}

void Pawn::sayMyName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK PAWN" << std::endl;
	}
	else
	{
		std::cout << "WHITE PAWN" << std::endl;
	}
}

void Pawn::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<PossibleMove> moves;

	if (m_pos.second + m_dy == 0 || m_pos.second + m_dy == 7)
	{
		if (field[m_pos.first][m_pos.second + m_dy] == NULL)
		{
			struct PossibleMove p1 = { m_pos.first, m_pos.second + m_dy, Piece::NEWPIECE };
			moves = pushMove(moves,
				p1,
				getOwnKing(field),
				field,
				checkCheck);
		}
	}
	else
	{
		if (field[m_pos.first][m_pos.second + m_dy] == NULL)
		{
			struct PossibleMove p1 = { m_pos.first, m_pos.second + m_dy, Piece::NORMAL };
			moves = pushMove(moves,
				p1,
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if ((m_pos.second + 2 * m_dy >= 0) && (m_pos.second + 2 * m_dy <= 7))
	{
		if (field[m_pos.first][m_pos.second + 2 * m_dy] == NULL && !m_hasMoved)
		{
			struct PossibleMove p1 = { m_pos.first, m_pos.second + 2 * m_dy, Piece::NORMAL };
			moves = pushMove(moves,
				p1,
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if (m_pos.first + 1 <= 7)
	{
		if (field[m_pos.first + 1][m_pos.second + m_dy] != NULL)
		{
			if (field[m_pos.first + 1][m_pos.second + m_dy]->getTeam() != m_team)
			{
				if (m_pos.second + m_dy == 0 || m_pos.second + m_dy == 7)
				{
					struct PossibleMove p1 = { m_pos.first + 1, m_pos.second + m_dy, Piece::NEWPIECE };
					moves = pushMove(moves,
						p1,
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					struct PossibleMove p1 = { m_pos.first + 1, m_pos.second + m_dy, Piece::NORMAL };
					moves = pushMove(moves,
						p1,
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}
	if (m_pos.first - 1 >= 0)
	{
		if (field[m_pos.first - 1][m_pos.second + m_dy] != NULL)
		{
			if (field[m_pos.first - 1][m_pos.second + m_dy]->getTeam() != m_team)
			{
				if (m_pos.second + m_dy == 0 || m_pos.second + m_dy == 7)
				{
					struct PossibleMove p1 = { m_pos.first - 1, m_pos.second + m_dy, Piece::NEWPIECE };
					moves = pushMove(moves,
						p1,
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					struct PossibleMove p1 = { m_pos.first - 1, m_pos.second + m_dy, Piece::NORMAL };
					moves = pushMove(moves,
						p1,
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}

	if (m_enPassant == std::pair<bool, int>(true, -1))
	{
		struct PossibleMove p1 = {m_pos.first + 1, m_pos.second + m_dy, Piece::ENPASSANT };
		moves = pushMove(moves,
			p1,
			getOwnKing(field),
			field,
			checkCheck);
	}
	if (m_enPassant == std::pair<bool, int>(true, 1))
	{
		struct PossibleMove p1 = { m_pos.first - 1, m_pos.second + m_dy, Piece::ENPASSANT };
		moves = pushMove(moves,
			p1,
			getOwnKing(field),
			field,
			checkCheck);
	}
	m_possibleMoves = moves;
}






