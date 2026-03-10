#pragma once /*_GAME_H_*/

/******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : ThuanDV12
Content      : Create a C++ console game Caro (10x10)
******************************************************************************/

#include <iostream>
#include <windows.h>
using namespace std;

/*******************************************************************************
* Definitions
******************************************************************************/
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_CYAN 11
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_WHITE 15

/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Prototypes
******************************************************************************/
/*!
 *    brief Function print main menu
 *
 *    return void
 */
void printMainMenu();

/*!
 *    brief Function print Play with bot menu
 *
 *    return void
 */
void printBOTMenu();

/*!
 *    brief Function print menu for player 1
 *
 *    param numPlayer is number of player
 *
 *    return the choice of menu
 */
int printPlayWithOtherPlayer1(int numPlayer);

/*!
 *    brief Function print menu for player 2 if player 1 is existing player
 *
 *    param numPlayer is number of player
 *
 *    return the choice of menu
 */
int printPlayWithOtherPlayer2a(int numPlayer);

/*!
 *    brief Function print menu for player 2 if player 1 is new player
 *
 *    param numPlayer is number of player
 *
 *    return the choice of menu
 */
int printPlayWithOtherPlayer2b(int numPlayer);

/*!
 *    brief Function print menu for making player
 *
 *    param orderPlayer is order of player in list
 *
 *    return void
 */
void printMakePlayerMenu(int orderPlayer);

/*!
 *    brief Function print menu for player with bot
 *
 *    param numPlayer is number of player
 *
 *    return the choice of menu
 */
int printPlayWithBOT(int numPlayer);

/*!
 *    brief Function print guide of game
 *
 *    return void
 */
void printGuide();

/*!
 *    brief Function choose bot level
 *
 *    return the bot level
 */
int chooseBotLevel();

/*!
 *    brief Function active virtual terminal
 *
 *    return the bot level
 */
void activateVirtualTerminal();

/**
* Colorize terminal colors ANSI escape sequences.
*
* @param font font color (0 to 15)
* @param back background color (0 to 15)
* @param style font style (1==bold, 4==underline)
**/
const char* colorize(int font, int back = 0, int style = -1);