#ifndef GAME_H // Replace PIECE_H with a unique identifier for each header file
#define GAME_H
#include "sdl_handler.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Piece.h"

class Game
{
private:
    /* data */
    	// 2D Field array, every Position has got a PIece::Team and a piece
	Piece* m_field[8][8];

    // disables enPassant for every Piece
    void disableEnPassant();

    // normal move
    void normal(int xStart, int yStart, int xEnd, int yEnd);

    // enpassant move
    void enPassant(int xStart, int yStart, int xEnd, int yEnd);

    // exchange move
    void exchange(int xStart, int yStart, int xEnd, int yEnd);

    // castles move
    void castles(int xStart, int yStart, int xEnd, int yEnd);

    // Background filename
    std::string m_backgroundFilename;

    // Decides whether if its black or whites turn
    Piece::Team m_turn;

    // handler
    sdl_handler* m_handler;

    // if true, disable en Passant! if false, dont
    bool m_checkEnPassant;

    // checks current game state, determines winner or remis
    void gameState();

    void RenderPieces();

    // every single piece
    Pawn* pawn_w1;
    Pawn* pawn_w2;
    Pawn* pawn_w3;
    Pawn* pawn_w4;
    Pawn* pawn_w5;
    Pawn* pawn_w6;
    Pawn* pawn_w7;
    Pawn* pawn_w8;
    Pawn* pawn_b1;
    Pawn* pawn_b2;
    Pawn* pawn_b3;
    Pawn* pawn_b4;
    Pawn* pawn_b5;
    Pawn* pawn_b6;
    Pawn* pawn_b7;
    Pawn* pawn_b8;
    Rook* rook_b1;
    Rook* rook_b2;
    Rook* rook_w1;
    Rook* rook_w2;
    Knight* Knight_b1;
    Knight* Knight_b2;
    Knight* Knight_w1;
    Knight* Knight_w2;
    Bishop* Bishop_b1;
    Bishop* Bishop_b2;
    Bishop* Bishop_w1;
    Bishop* Bishop_w2;
    King* King_b1;
    King* King_w1;
    Queen* queen_b1; 
    Queen* queen_w1;

    enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    King,
    Queen
    };

    enum class PieceColor {
    BLACK,
    WHITE
};
public:
    // Constructor
	Game(sdl_handler* handler);

    // Destructor
    ~Game();

	// returns a the Piece in field (row, col)
	Piece* getFieldPos(int row, int col);

    /*struct PossibleMove
    {
	    int xCoord, yCoord;
        Piece::MoveType moveType;
    };*/

    //Moves a piece
    void move(Piece* piece, Piece::PossibleMove move);

    // returns m_turn
    Piece::Team getTurn() { return m_turn; };

    // true, if the move is valid  ;  false if not
    bool isValidMove(int x, int y, Piece* piece);

    // calculates all allowed moves of every piece
    void calcAllMoves();

    void initializePieces();

    void initializeBoard();

    // light up the possible Moves
    void renderPossibleMoves(Piece* piece);

    // undos the renderPossibleMoves function
    void undoRenderPossibleMoves(Piece* piece);
};
#endif