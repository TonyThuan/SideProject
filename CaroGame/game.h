#pragma once /*_GAME_H_*/

/******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : ThuanDV12
Content      : Create a C++ console game Caro (10x10)
******************************************************************************/
#include "player.h"
#include "BOT.h"

/*******************************************************************************
* Definitions
******************************************************************************/
#define BOARD_SIZE 15
#define PLAYER1_SYMBOL 'X'
#define PLAYER2_SYMBOL 'O'
#define EMPTY ' '
#define WIN_CONDITION 5 /* Number of same moves in a row horizontally, vertically or diagonally for winning */
#define SAVED_GAME 10
#define EASY 0
#define NORMAL 1
#define HARD 2

/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* Prototypes
******************************************************************************/
/*
 *    Class: GAME
 *    Manage game's information
 */
class GAME
{
private:
    pair<string, int> m_player1;           /* 1st element is name, 2nd: win/draw/lose status */
    pair<string, int> m_player2;           /* 1st element is name, 2nd: win/draw/lose status */
    vector<pair<int, int>> m_moveStatus;   /* Vector of move status: 1st element is row, 2nd element is column */

public:
    friend class GAME_FACTORY;
};

/*
 *    Class: GAME_FACTORY
 *    Manage games' information
 */
class GAME_FACTORY
{
    vector<GAME> m_game;    /* Store games' information */
    int m_numGame;          /* Number of completed game */

public:
    GAME_FACTORY() : m_numGame(0) {};
    GAME* createGame(PLAYER& player1, PLAYER& player2);
    GAME* createGame(PLAYER& player, int botLevel);
    void saveGame(GAME game);
    void loadGameFromFile(const string& fileName);
    void saveGameToFile(const string& fileName);
    void showGameInfo();
    void showGameMove(int index);
};

/*!
 *    brief Function check validation of move
 *
 *    param board[][BOARD_SIZE] is board status
 *    param currentMove is coordinate of current move
 *
 *    return true if current move is valid move and vice versa
 */
extern bool isValidMove(char board[][BOARD_SIZE], pair<int, int> currentMove);

/*!
 *    brief Function check winning condition
 *
 *    param board[][BOARD_SIZE] is board status
 *    param currentMove is coordinate of current move
 *    param symbol is symbol of current player
 *
 *    return true if winning condition happend and vice versa
 */
extern bool checkWin(char board[][BOARD_SIZE], pair<int, int> currentMove, char symbol);

/*!
 *    brief Function check board is full
 *
 *    param board[][BOARD_SIZE] is board status
 *
 *    return true if board is full and vice versa
 */
extern bool isBoardFull(char board[][BOARD_SIZE]);