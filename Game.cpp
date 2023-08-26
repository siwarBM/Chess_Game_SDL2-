#include "Game.h"
#include <iostream>

Game::Game(sdl_handler* handler)
       :pawn_w1(new Pawn(Piece::WHITE, std::pair<int, int>(0, 1), handler)),
        pawn_w2(new Pawn(Piece::WHITE, std::pair<int, int>(1, 1), handler)),
        pawn_w3(new Pawn(Piece::WHITE, std::pair<int, int>(2, 1), handler)),
        pawn_w4(new Pawn(Piece::WHITE, std::pair<int, int>(3, 1), handler)),
        pawn_w5(new Pawn(Piece::WHITE, std::pair<int, int>(4, 1), handler)),
        pawn_w6(new Pawn(Piece::WHITE, std::pair<int, int>(5, 1), handler)),
        pawn_w7(new Pawn(Piece::WHITE, std::pair<int, int>(6, 1), handler)),
        pawn_w8(new Pawn(Piece::WHITE, std::pair<int, int>(7, 1), handler)),
        pawn_b1(new Pawn(Piece::BLACK, std::pair<int, int>(0, 6), handler)),
        pawn_b2(new Pawn(Piece::BLACK, std::pair<int, int>(1, 6), handler)),
        pawn_b3(new Pawn(Piece::BLACK, std::pair<int, int>(2, 6), handler)),
        pawn_b4(new Pawn(Piece::BLACK, std::pair<int, int>(3, 6), handler)),
        pawn_b5(new Pawn(Piece::BLACK, std::pair<int, int>(4, 6), handler)),
        pawn_b6(new Pawn(Piece::BLACK, std::pair<int, int>(5, 6), handler)),
        pawn_b7(new Pawn(Piece::BLACK, std::pair<int, int>(6, 6), handler)),
        pawn_b8(new Pawn(Piece::BLACK, std::pair<int, int>(7, 6), handler)),
        rook_b1(new Rook(Piece::BLACK, std::pair<int, int>(0, 7), handler)),
        rook_b2(new Rook(Piece::BLACK, std::pair<int, int>(7, 7), handler)),
        rook_w1(new Rook(Piece::WHITE, std::pair<int, int>(0, 0), handler)),
        rook_w2(new Rook(Piece::WHITE, std::pair<int, int>(7, 0), handler)),
        Knight_b1(new Knight(Piece::BLACK, std::pair<int, int>(1, 7), handler)),
        Knight_b2(new Knight(Piece::BLACK, std::pair<int, int>(6, 7), handler)),
        Knight_w1(new Knight(Piece::WHITE, std::pair<int, int>(1, 0), handler)),
        Knight_w2(new Knight(Piece::WHITE, std::pair<int, int>(6, 0), handler)),
        Bishop_b1(new Bishop(Piece::BLACK, std::pair<int, int>(2, 7), handler)),
        Bishop_b2(new Bishop(Piece::BLACK, std::pair<int, int>(5, 7), handler)),
        Bishop_w1(new Bishop(Piece::WHITE, std::pair<int, int>(2, 0), handler)),
        Bishop_w2(new Bishop(Piece::WHITE, std::pair<int, int>(5, 0), handler)),
        King_b1(new King(Piece::BLACK, std::pair<int, int>(3, 7), handler)),
        King_w1(new King(Piece::WHITE, std::pair<int, int>(3, 0), handler)),
        queen_b1(new Queen(Piece::BLACK, std::pair<int, int>(4, 7), handler)),
        queen_w1(new Queen(Piece::WHITE, std::pair<int, int>(4, 0), handler)),
        m_turn(Piece::WHITE),
        m_handler(handler),
        m_checkEnPassant(true)
{
    // Create Pieces.
    m_field[0][7] = rook_b1;
    m_field[7][7] = rook_b2;
    m_field[0][0] = rook_w1;
    m_field[7][0] = rook_w2;

    m_field[1][7] = Knight_b1;
    m_field[6][7] = Knight_b2;
    m_field[1][0] = Knight_w1;
    m_field[6][0] = Knight_w2;

    m_field[2][7] = Bishop_b1;
    m_field[5][7] = Bishop_b2;
    m_field[2][0] = Bishop_w1;
    m_field[5][0] = Bishop_w2;

    m_field[3][7] = King_b1;
    m_field[3][0] = King_w1;

    m_field[4][7] = queen_b1;
    m_field[4][0] = queen_w1;

    m_field[0][1] = pawn_w1;
    m_field[1][1] = pawn_w2;
    m_field[2][1] = pawn_w3;
    m_field[3][1] = pawn_w4;
    m_field[4][1] = pawn_w5;
    m_field[5][1] = pawn_w6;
    m_field[6][1] = pawn_w7;
    m_field[7][1] = pawn_w8;

    m_field[0][6] = pawn_b1;
    m_field[1][6] = pawn_b2;
    m_field[2][6] = pawn_b3;
    m_field[3][6] = pawn_b4;
    m_field[4][6] = pawn_b5;
    m_field[5][6] = pawn_b6;
    m_field[6][6] = pawn_b7;
    m_field[7][6] = pawn_b8;

    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
        {
            m_field[j][i] = NULL;
        }
    }

    calcAllMoves();
}

Game::~Game()
{
}


Piece* Game::getFieldPos(int row, int col)
{
    return m_field[row][col];
}


void Game::move(Piece* start, Piece::PossibleMove move)
{
    if (m_checkEnPassant)
    {
        disableEnPassant();
    }
    else
    {
        m_checkEnPassant = true;
    }

    switch (move.moveType)
    {
        case Piece::NORMAL:
            normal(start->getPos().first, start->getPos().second, move.xCoord, move.yCoord);
            break;
        case Piece::CASTLE:
            castles(start->getPos().first, start->getPos().second, move.xCoord, move.yCoord);
            break;
        case Piece::ENPASSANT:
            enPassant(start->getPos().first, start->getPos().second, move.xCoord, move.yCoord);
            break;
        case Piece::NEWPIECE:
            exchange(start->getPos().first, start->getPos().second, move.xCoord, move.yCoord);
            break;
        default:
            break;
    }

    gameState();
}


void Game::normal(int xStart, int yStart, int xEnd, int yEnd)
{
    m_field[xEnd][yEnd] = getFieldPos(xStart, yStart);
    m_field[xEnd][yEnd]->m_hasMoved = true;
    m_field[xStart][yStart] = NULL;
    m_handler->undoPieceRender(xStart, yStart);
    m_field[xEnd][yEnd]->setPosition(std::pair<int, int>(xEnd, yEnd));
    if (m_field[xEnd][yEnd] != NULL)
    {
        m_handler->undoPieceRender(xEnd, yEnd);
    }
    m_field[xEnd][yEnd]->render();

    if (m_field[xEnd][yEnd]->getType() == Piece::PAWN)
    {
        if (abs(yEnd - yStart) == 2)
        {
            if (xEnd - 1 >= 0)
            {
                if (m_field[xEnd - 1][yEnd] != NULL)
                {
                    if (m_field[xEnd - 1][yEnd]->getType() == Piece::PAWN)
                    {
                        Pawn* pwn = static_cast<Pawn*>(m_field[xEnd - 1][yEnd]);
                        pwn->setEnPassant(std::pair<bool, int>(true, -1));
                        m_checkEnPassant = false;
                    }
                }
            }

            if (xEnd + 1 <= 7)
            {
                if (m_field[xEnd + 1][yEnd] != NULL)
                {
                    if (m_field[xEnd + 1][yEnd]->getType() == Piece::PAWN)
                    {
                        Pawn* pwn = static_cast<Pawn*>(m_field[xEnd + 1][yEnd]);
                        pwn->setEnPassant(std::pair<bool, int>(true, 1));
                        m_checkEnPassant = false;
                    }
                }
            }
        }
    }
}


void Game::enPassant(int xStart, int yStart, int xEnd, int yEnd)
{
    Pawn* pawn_start = static_cast<Pawn*>(m_field[xStart][yStart]);
    m_field[xEnd][yEnd - pawn_start->m_dy] = NULL;
    m_field[xEnd][yEnd] = getFieldPos(xStart, yStart);
    m_field[xEnd][yEnd]->m_hasMoved = true;
    m_field[xStart][yStart] = NULL;
    m_handler->undoPieceRender(xStart, yStart);
    m_handler->undoPieceRender(xEnd, yEnd - pawn_start->m_dy);
    m_field[xEnd][yEnd]->setPosition(std::pair<int, int>(xEnd, yEnd));
    m_field[xEnd][yEnd]->render();
}


void Game::exchange(int xStart, int yStart, int xEnd, int yEnd)
{
    SDL_Texture* text_rook = m_handler->loadImage("img/Chess_rlt60.png");
    SDL_Texture* text_knight = m_handler->loadImage("img/Chess_nlt60.png");
    SDL_Texture* text_bishop = m_handler->loadImage("img/Chess_blt60.png");
    SDL_Texture* text_queen = m_handler->loadImage("img/Chess_qlt60.png");
    int y_draw = 0;
    Piece::Team team = Piece::WHITE;

    if (m_field[xStart][yStart]->getTeam() == Piece::BLACK)
    {
        text_rook = m_handler->loadImage("img/Chess_rdt60.png");
        text_knight = m_handler->loadImage("img/Chess_ndt60.png");
        text_bishop = m_handler->loadImage("img/Chess_bdt60.png");
        text_queen = m_handler->loadImage("img/Chess_qdt60.png");
        y_draw = 3 * m_handler->SCREEN_HEIGHT / 4;
        team = Piece::BLACK;
    }

    //SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
    SDL_SetRenderDrawColor(m_handler->m_renderer, 0, 255, 0, 255);
    SDL_Rect rectangle = {0,
                          y_draw,
                          m_handler->SCREEN_WIDTH / 4,
                          m_handler->SCREEN_HEIGHT / 4 };
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    SDL_Rect src = { 0, 0, 60, 60 };
    m_handler->DrawRectangle(src, rectangle, text_rook);

    SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
    rectangle.x = m_handler->SCREEN_WIDTH / 4;
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    m_handler->DrawRectangle(src, rectangle, text_knight);

    //SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
    SDL_SetRenderDrawColor(m_handler->m_renderer, 0, 255, 0, 255);
    rectangle.x = 2 * m_handler->SCREEN_WIDTH / 4;
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    m_handler->DrawRectangle(src, rectangle, text_bishop);

    SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
    rectangle.x = 3 * m_handler->SCREEN_WIDTH / 4;
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    m_handler->DrawRectangle(src, rectangle, text_queen);

    bool quit = false;
    int x = -1;
    int y = -1;

    Piece* clickedOn = NULL;

    std::cout << m_handler;
    
    while (quit == false)
    {
        while (SDL_PollEvent(&m_handler->m_event))
        {
            if (m_handler->m_event.type == SDL_QUIT)
            {
                quit = true;
            }

            if (m_handler->m_event.type == SDL_MOUSEBUTTONDOWN)
            {
                x = m_handler->m_event.button.x / 160;
                y = m_handler->m_event.button.y / 160;
                
                if (y >= y_draw / 160 && y < y_draw / 160 + 1)
                {
                    if (x < m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Rook(team ,std::pair<int, int>(xEnd, yEnd), m_handler);
                    }
                    else if (x < 2 * m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Knight(team ,std::pair<int, int>(xEnd, yEnd), m_handler);
                    }
                    else if (x < 3 * m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Bishop(team ,std::pair<int, int>(xEnd, yEnd), m_handler);
                    }
                    else if (x <= 4 * m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Queen(team ,std::pair<int, int>(xEnd, yEnd), m_handler);
                    }
                    std::cout << x << " " << m_handler->SCREEN_WIDTH / 640 << std::endl;
                }
            }
            
            if (m_handler->m_event.type == SDL_MOUSEBUTTONUP && clickedOn != NULL)
            {
                quit = true;
            }
        }
    }

    m_field[xEnd][yEnd] = clickedOn;
    m_field[xStart][yStart] = NULL;
    m_handler->undoPieceRender(xStart, yStart);
    m_handler->renderBackground();
    
    for (int i = 0; i < m_handler->PIECE_NUMBER; i++)
    {
        for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
        {
            if (m_field[i][j] != NULL)
            {
                m_field[i][j]->render();
            }
        }
    }
    
    SDL_DestroyTexture(text_rook);
    SDL_DestroyTexture(text_bishop);
    SDL_DestroyTexture(text_knight);
    SDL_DestroyTexture(text_queen);
}


void Game::castles(int xStart, int yStart, int xEnd, int yEnd)
{
    if (xEnd == 0)
    {
        m_field[2][yEnd] = m_field[4][yEnd];
        m_field[3][yEnd] = m_field[0][yEnd];
        m_field[2][yEnd]->m_hasMoved = true;
        m_field[3][yEnd]->m_hasMoved = true;
        m_field[2][yEnd]->setPosition(std::pair<int, int>(2, yEnd));
        m_field[3][yEnd]->setPosition(std::pair<int, int>(3, yEnd));
        m_field[4][yEnd] = NULL;
        m_field[0][yEnd] = NULL;
        m_handler->undoPieceRender(4, yEnd);
        m_handler->undoPieceRender(0, yEnd);
        m_field[2][yEnd]->render();
        m_field[3][yEnd]->render();
    }
    else
    {
        m_field[6][yEnd] = m_field[4][yEnd];
        m_field[5][yEnd] = m_field[7][yEnd];
        m_field[6][yEnd]->m_hasMoved = true;
        m_field[5][yEnd]->m_hasMoved = true;
        m_field[6][yEnd]->setPosition(std::pair<int, int>(6, yEnd));
        m_field[5][yEnd]->setPosition(std::pair<int, int>(5, yEnd));
        m_field[4][yEnd] = NULL;
        m_field[7][yEnd] = NULL;
        m_handler->undoPieceRender(4, yEnd);
        m_handler->undoPieceRender(7, yEnd);
        m_field[6][yEnd]->render();
        m_field[5][yEnd]->render();
    }
}

void Game::gameState()
{
    bool lost = true;
    std::string message;
    King* pivot = King_b1;

    if (m_turn == Piece::BLACK)
    {
        pivot = King_w1;
    }

    pivot->setCheck(m_field, King_w1->getPos().first, King_w1->getPos().second);
    for (int i = 0; i < m_handler->PIECE_NUMBER; i++)
    {
        for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
        {
            if (m_field[i][j] != NULL)
            {
                if (m_field[i][j]->getTeam() != m_turn)
                {
                    m_field[i][j]->calcPossibleMoves(m_field, true);
                    if (!m_field[i][j]->getPossibleMoves().empty())
                    {
                        lost = false;
                    }
                }
            }
        }
    }

    if (pivot->getCheck() && lost)
    {
        message = (m_turn == Piece::BLACK) ? "Black wins!" : "White wins!";
        /*if (m_turn == Piece::BLACK)
        {
            std::cout << "Black wins!";
        }
        else
        {
            std::cout << "White wins!";
        }*/
        std::cout << message << std::endl;
    }
    else if (lost)
    {
        message = (m_turn == Piece::BLACK) ? "Black Remis!" : "White Remis!";
       /*if (m_turn == Piece::BLACK)
        {
            std::cout << "Remis!";
        }
        else
        {
            std::cout << "Remis!";
        }*/
    }
    //var = (y < 10) ? 30 : 40;
    if (m_turn == Piece::BLACK)
    {
        m_turn = Piece::WHITE;
    }
    else
    {
        m_turn = Piece::BLACK;
    }

}


void Game::disableEnPassant()
{
    for (int i = 0; i < m_handler->PIECE_NUMBER; i++)
    {
        for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
        {
            if (m_field[i][j] != NULL)
            {
                if (m_field[i][j]->getType() == Piece::PAWN)
                {
                    Pawn* pwn = static_cast<Pawn*>(m_field[i][j]);
                    pwn->setEnPassant(std::pair<bool, int>(false, 0));
                }
            }
        }
    }
}
// Added by me based on the cherno.
/*struct PossibleMove
{
    int xCoord, yCoord;
    Piece::MoveType MoveType;
};*/
void Game::renderPossibleMoves(Piece* piece)
{
    piece->calcPossibleMoves(m_field, true);
    std::vector<Piece::PossibleMove> possible = piece->getPossibleMoves();
    SDL_Rect rectangle;
    for (const Piece::PossibleMove& value : possible) {
        if ((value.xCoord % 2 == 0 && value.yCoord % 2 == 1) || (value.xCoord % 2 == 1 && value.yCoord % 2 == 0))
        {
            SDL_SetRenderDrawColor(m_handler->m_renderer, 164, 211, 238, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(m_handler->m_renderer, 164, 211, 238, 255);
        }
        rectangle = { value.xCoord * m_handler->SCREEN_WIDTH / m_handler->PIECE_NUMBER,
                      value.yCoord* m_handler->SCREEN_HEIGHT / m_handler->PIECE_NUMBER,
                      m_handler->SCREEN_WIDTH / m_handler->PIECE_NUMBER,
                      m_handler->SCREEN_HEIGHT / m_handler->PIECE_NUMBER };
        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);

        for (int i = 0; i < m_handler->PIECE_NUMBER; i++)
        {
            for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
            {
                if (m_field[i][j] != NULL)
                {
                    m_field[i][j]->render();
                }
            }
        }
    } 
}

void Game::undoRenderPossibleMoves(Piece* piece)
{
    std::vector<Piece::PossibleMove> possible = piece->getPossibleMoves();
    for (const Piece::PossibleMove& value : possible) {
        if ((value.xCoord % 2 == 0 && value.yCoord % 2 == 1) || (value.xCoord % 2 == 1 && value.yCoord % 2 == 0))
        {
            //SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
            // Green Color.
            SDL_SetRenderDrawColor(m_handler->m_renderer, 0, 255, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
        }
        SDL_Rect rectangle = { value.xCoord * m_handler->SCREEN_WIDTH / m_handler->PIECE_NUMBER,
                                  value.yCoord* m_handler->SCREEN_HEIGHT / m_handler->PIECE_NUMBER,
                                  m_handler->SCREEN_WIDTH / m_handler->PIECE_NUMBER,
                                  m_handler->SCREEN_HEIGHT / m_handler->PIECE_NUMBER };
        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);

        for (int i = 0; i < m_handler->PIECE_NUMBER; i++)
        {
            for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
            {
                if (m_field[i][j] != NULL)
                {
                    m_field[i][j]->render();
                }
            }
        }
    }
}

void Game::calcAllMoves()
{
    std::cout << " siwar New Move" << std::endl;
    for (int i = 0; i <m_handler->PIECE_NUMBER; i++)
    {
        for (int j = 0; j < m_handler->PIECE_NUMBER; j++)
        {
            if (m_field[i][j] != NULL)
            {
                m_field[i][j]->calcPossibleMoves(m_field, true);
                std::cout << " Pointer for piece is not null" << std::endl;
            }
            else
            {
                std::cout << "Piece null pointer" << std::endl;
            }
        }
    }
}

bool Game::isValidMove(int x, int y, Piece* piece)
{
    std::vector<Piece::PossibleMove> list = piece->getPossibleMoves();
    for (const Piece::PossibleMove& value : list) {
        if (value.xCoord == x && value.yCoord == y)
        {
            return true;
        }
    }
    return false;
}