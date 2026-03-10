#pragma once /*_PLAYER_H_*/

/******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : ThuanDV12
Content      : Create a C++ console game Caro (10x10)
******************************************************************************/

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <utility>
#include <sstream>
#include "menu.h"
using namespace std;

/*******************************************************************************
* Definitions
******************************************************************************/
#define WIN_POINT 10000
#define DRAW_POINT 0
#define LOSE_POINT -10000
#define IS_NEW_PLAYER -1
#define IS_NOT_NEW_PLAYER -2

/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Prototypes
******************************************************************************/
/*
    Class: PLAYER
    Manage a player's informations
*/
class PLAYER
{
private:
    string m_name;   /* Name */
    int m_winNum;    /* Number of wins */
    int m_loseNum;   /* Number of loses */
    int m_drawNum;   /* Number of draws */
    int m_score;     /* Number of scores */

public:
    PLAYER() : m_winNum(0), m_loseNum(0), m_drawNum(0), m_score(0) {};
    PLAYER operator=(PLAYER player);
    void updateScore(int score);
    string getPlayerName();
    int getScore();
    friend class PLAYER_FACTORY;
    friend class GAME_FACTORY;
};

/*
    Class: PLAYER_FACTORY
    Manage players' information
*/
class PLAYER_FACTORY
{
private:
    vector<PLAYER> m_player;    /* Store games' info */
    int m_numPlayer;            /* Number of players */

public:
    PLAYER_FACTORY() : m_numPlayer(0) {};
    PLAYER* makePlayer(int& playerIndex);
    void savePlayer(PLAYER player, int playerIndex);
    void loadPlayerFromFile(const string& fileName);
    void savePlayerToFile(const string& fileName);
    int getPlayerNumber();
    void showPlayerInfo(string namePlayer);
    void showPlayerList();
};