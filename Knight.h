#ifndef KNIGHT_H // Replace PIECE_H with a unique identifier for each header file
#define KNIGHT_H
#pragma once
#include "Piece.h"

// Forward declaration of Piece class
class Piece;
class Knight : public Piece
{
public:
    Knight(Team team, std::pair<int, int> pos, sdl_handler* handler);

    // calls name an
    void sayMyName();

    // calculates the possible moves
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);
};
#endif

