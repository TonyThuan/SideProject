/*******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : ThuanDV12
Content      : Create a C++ console game Caro (10x10).
******************************************************************************/
#include "game.h"

/*******************************************************************************
* Definitions
******************************************************************************/


/*******************************************************************************
* Variables
******************************************************************************/

/*******************************************************************************
* API
******************************************************************************/
/*!
 *    brief Function print main menu
 *
 *    return void
 */
void printMainMenu()
{
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------MAIN MENU--------*\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << "Press number to choice:_\n";
    cout << "1.Play with Other Player\n";
    cout << "2.Play with BOT\n";
    cout << "3.Watch replay\n";
    cout << "4.Player's Information\n";
    cout << "5.Guild\n";
    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "6.Exit\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
}

/*!
 *    brief Function print Play with bot menu
 *
 *    return void
 */
void printBOTMenu()
{
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------PLAY WITH BOT--------*\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << "Press number to choice:_\n";
    cout << "1.Easy Mode\n";
    cout << "2.Normal Mode\n";
    cout << "3.Hard Mode\n";
    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "4.Back to MAIN MENU\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
}

/*!
 *    brief Function print menu for player 1
 *
 *    param numPlayer is number of player
 * 
 *    return the choice of menu
 */
int printPlayWithOtherPlayer1(int numPlayer)
{
    string menu;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    if (0 == numPlayer)
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------PLAY WITH OTHER PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "Press number to choice:_\n";
        cout << "2.Create a New Player\n";
        SetConsoleTextAttribute(consoleColor, COLOR_RED);
        cout << "3.Back to MAIN MENU\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);

        cin.clear();
        getline(cin, menu);
        while (stoi(menu) != 2 && stoi(menu) != 3)
        {
            cout << "Invalid choice. Choose again: ";
            cin.clear();
            getline(cin, menu);
        }
    }
    else
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------PLAY WITH OTHER PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "Press number to choice:_\n";
        cout << "1.Choose an Existing Player\n";
        cout << "2.Create a New Player\n";
        SetConsoleTextAttribute(consoleColor, COLOR_RED);
        cout << "3.Back to MAIN MENU\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);

        cin.clear();
        getline(cin, menu);
        while (stoi(menu) < 1 || stoi(menu) > 3)
        {
            cout << "Invalid choice. Choose again: ";
            cin.clear();
            getline(cin, menu);
        }
    }

    return stoi(menu);
}

/*!
 *    brief Function print menu for player 2 if player 1 is existing player
 *
 *    param numPlayer is number of player
 *
 *    return the choice of menu
 */
int printPlayWithOtherPlayer2a(int numPlayer)
{
    string menu;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    if (2 > numPlayer) /* If only have 1 player */
    {
        menu = "2";
    }
    else /* If have more than 1 player */
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------PLAY WITH OTHER PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "Press number to choice:_\n";
        cout << "1.Choose an Existing Player\n";
        cout << "2.Create a New Player\n";

        cin.clear();
        getline(cin, menu);
        while (stoi(menu) < 1 || stoi(menu) > 2)
        {
            cout << "Invalid choice. Choose again: ";
            cin.clear();
            cin >> menu;
        }
    }

    return stoi(menu);
}

/*!
 *    brief Function print menu for player 2 if player 1 is new player
 *
 *    param numPlayer is number of player
 *
 *    return the choice of menu
 */
int printPlayWithOtherPlayer2b(int numPlayer)
{
    string menu;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    if (1 > numPlayer) /* If have no existing player */
    {
        menu = "2";
    }
    else /* If have at least 1 player */
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------PLAY WITH OTHER PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "Press number to choice:_\n";
        cout << "1.Choose an Existing Player\n";
        cout << "2.Create a New Player\n";

        cin >> menu;
        while (stoi(menu) < 1 || stoi(menu) > 2)
        {
            cout << "Invalid choice. Choose again: ";
            cin.clear();
            cin >> menu;
        }
    }

    return stoi(menu);
}

/*!
 *    brief Function print menu for making player
 *
 *    param orderPlayer is order of player in list
 *
 *    return void
 */
void printMakePlayerMenu(int orderPlayer)
{
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------PLAYER " << orderPlayer << "--------*\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << "Press number to choice:_\n";
    cout << "1.Choose an Existing player\n";
    cout << "2.Create a New Player\n";
    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "3.Back to MAIN MENU\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
}

/*!
 *    brief Function print menu for player with bot
 *
 *    param numPlayer is number of player
 *
 *    return the choice of menu
 */
int printPlayWithBOT(int numPlayer)
{
    string menu;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    if (0 == numPlayer)
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------PLAY WITH OTHER PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "Press number to choice:_\n";
        cout << "2.Create a New Player\n";
        SetConsoleTextAttribute(consoleColor, COLOR_RED);
        cout << "3.Back to MAIN MENU\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);

        cin.clear();
        getline(cin, menu);
        while (stoi(menu) != 2 && stoi(menu) != 3)
        {
            cout << "Invalid choice. Choose again: ";
            cin.clear();
            getline(cin, menu);
        }
    }
    else
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------PLAY WITH OTHER PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "Press number to choice:_\n";
        cout << "1.Choose an Existing Player\n";
        cout << "2.Create a New Player\n";
        SetConsoleTextAttribute(consoleColor, COLOR_RED);
        cout << "3.Back to MAIN MENU\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);

        cin.clear();
        getline(cin, menu);
        while (stoi(menu) < 1 || stoi(menu) > 3)
        {
            cout << "Invalid choice. Choose again: ";
            cin.clear();
            getline(cin, menu);
        }
    }

    return stoi(menu);
}

/*!
 *    brief Function print guide of game
 *
 *    return void
 */
void printGuide()
{
    string choice;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------CARO GAME GUIDE--------*\n\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << "- Player 1 place X, player 2 place O\n\n";
    cout << "- Two players take turns filling in the blank cells in the board\n";
    cout << "  Example: Player 1 enters 3 4 to place X in cell (3th row, 4th column)\n\n";
    cout << "- When a player has 4 cells or in a row horizontally, vertically or diagonally,\n";
    cout << "  that player wins and GAME is OVER\n\n";
    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "0. Back to MAIN MENU\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);

    getline(cin, choice);
}

/*!
 *    brief Function choose bot level
 *
 *    return the bot level
 */
int chooseBotLevel()
{
    string choice = "";
    int gameLevel = -1;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------PLAY WITH BOT--------*\n";
    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "0. Back to MAIN MENU\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << "1. EASY\n";
    cout << "2. NORMAL\n";
    cout << "3. HARD\n";
    cout << "Choose BOT level: ";
    getline(cin, choice);

    while ("0" != choice && "1" != choice && "2" != choice && "3" != choice)
    {
        cout << "Invalid choice. Press again: ";
        getline(cin, choice);
    }

    if ("0" == choice)
        gameLevel = -1;
    else if ("1" == choice)
        gameLevel = EASY;
    else if ("2" == choice)
        gameLevel = NORMAL;
    else if ("3" == choice)
        gameLevel = HARD;

    return gameLevel;
}