#ifndef QUEEN_H // Replace PIECE_H with a unique identifier for each header file
#define QUEEN_H
#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
public:
    Queen(Team team, std::pair<int, int> pos, sdl_handler* handler);

    // prints name of piece
    void sayMyName();

    // calculates the possible moves
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);
};
#endif
