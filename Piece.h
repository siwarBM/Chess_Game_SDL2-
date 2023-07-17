#ifndef PIECE_H // Replace PIECE_H with a unique identifier for each header file
#define PIECE_H

#pragma once

#include <utility>
#include <vector>
#include "sdl_handler.h"
#include <SDL.h>
#include <tuple>

class King;
class Piece
{
public:
    enum Team { BLACK, WHITE, NONE };

	enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };

	enum MoveType { NORMAL, CASTLE, ENPASSANT, NEWPIECE, INIT };
    
	struct PossibleMove
    {
	    int xCoord, yCoord;
        Piece::MoveType moveType;
    };

	// returns list of possible Moves
	std::vector<PossibleMove> getPossibleMoves() { return m_possibleMoves; };

	// return whether BLACK or WHITE
	Team getTeam() { return m_team; };

	// sets new position
	void setPosition(std::pair<int, int> newPos) { m_pos = newPos; };

	// return position of piece
	std::pair<int, int> getPos() { return m_pos; };

	// Constructor
	Piece(Team team, std::pair<int,int> pos, sdl_handler* handler, PieceType type);

	// Copy-Constructor
	Piece(const Piece& piece);

	// Destructor
	~Piece();

	//render this piece
	void render();

	// prints name of piece
	virtual void sayMyName();

	// calculates every possible Move this piece can do
	virtual void calcPossibleMoves(Piece* field[8][8], bool checkCheck) = 0;

	// true, if piece has moved
	bool m_hasMoved;

	// returns type of piece
	PieceType getType() { return m_type; };
protected:
   	// texture of this piece
	SDL_Texture* m_texture;

	// SDL Handler
	sdl_handler* m_handler;

	// Team this piece plays for
	Team m_team;
 
	// The Type of Piece
	PieceType m_type;

	// List of possible Moves this piece can do <row, col>
	std::vector<PossibleMove> m_possibleMoves;
	
	// Position of the piece
	std::pair<int, int> m_pos;

	// pushes the move, if its allowed.
	// simulates the move, and checks wheter the own king is still checked
	// if king is in check after simulated move, the move is not allowed
	// if checkCheck is true the king simulation will determine whether the move is allowed or not
	// if checkCheck is false, we will just push the move. checkCheck is only false in King's setCheck function,
	// because otherwise it will produce stack overflow (pushMove calls setCheck, setCheck calls pushMove and so on)
	std::vector<PossibleMove> pushMove(std::vector<PossibleMove> moveList,
																 PossibleMove move,
																 King* king,
																 Piece* field[8][8],
																 bool checkCheck);

	// returns king of own team from field
	King* getOwnKing(Piece* field[8][8]);
    /* data */
};
#endif