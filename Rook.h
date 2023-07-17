#ifndef ROOK_H // Replace PIECE_H with a unique identifier for each header file
#define ROOK_H
#pragma once
#include "Piece.h"

class Rook :
    public Piece
{
public:
    // Constructor
    Rook(Team team, std::pair<int, int> pos, sdl_handler* handler);

    // prints name of piece
    void sayMyName();

    // Destructor
    ~Rook();

    // calculates the possible moves
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);
};
#endif


