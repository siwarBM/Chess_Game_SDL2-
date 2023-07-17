#ifndef BISHOP_H // Replace PIECE_H with a unique identifier for each header file
#define BISHOP_H
#include "Piece.h"
#include "King.h"

class Bishop : public Piece
{
private:
    /* data */
public:
        //Constructor
    Bishop(Team team, std::pair<int, int> pos, sdl_handler* handler);

    // used to debug some stuff
    void sayMyName();

    // calculates the possible moves, 
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

    ~Bishop();
};
#endif

