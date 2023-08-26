#ifndef MAINLOOP_H // Replace PIECE_H with a unique identifier for each header file
#define MAINLOOP_H

#include "Game.h"
#include "Piece.h"

class mainloop
{
private:
    /* data */
public:
    static void run();
    static bool isvalidmove(Piece* clickedOn, Game* game);
    mainloop(/* args */);
    ~mainloop();
};
#endif
