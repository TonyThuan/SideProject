/*******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : ThuanDV12
Content      : Create a C++ console game Caro (10x10).
 ******************************************************************************/

#include "game.h"
using namespace std;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define YES "y"
#define NO "n"
#define EXIT "6"

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

 /*!
  *    brief Function setup all game for 2 players
  *
  *    param playerGate is object save players' information
  *    param gameGate is object save games' information
  *
  *    return void
  */
void playWithOtherPlayer(PLAYER_FACTORY& playerGate, GAME_FACTORY &gameGate);

/*!
 *    brief Function make a game for 2 players
 *
 *    param player1 is object save 1st player's info
 *    param player2 is object save 2nd player's info
 *    param playerIndex1 is index of player 1 in player list.
 *    playerIndex1 = -1 is new player
 *    param playerIndex2 is index of player 2 in player list.
 *    playerIndex2 = -1 is new player
 *
 *    return void
 */
void makeGame(PLAYER*& player1, PLAYER*& player2, int& playerIndex1, int& playerIndex2,
    PLAYER_FACTORY& playerGate, GAME_FACTORY& gameGate);

/*!
 *    brief Function setup all game for BOT and player
 *
 *    param playerGate is object save players' information
 *    param gameGate is object save games' information
 *
 *    return void
 */
void playWithBOT(PLAYER_FACTORY& playerGate, GAME_FACTORY& gameGate);

/*!
 *    brief Function make a game for BOT and player
 *
 *    param player is object save player's info
 *    param playerIndex is index of player in player list.
 *    playerIndex = -1 is new player
 *    param botLevel is a level of the BOT (Easy, Normal, Hard)
 *
 *    return void
 */
void makeGame(PLAYER*& player, int& playerIndex, PLAYER_FACTORY& playerGate, GAME_FACTORY& gameGate, int botLevel);

/*!
 *    brief Function show information of players
 *
 *    param playerGate is object save players' information
 *
 *    return void
 */
void playerInfo(PLAYER_FACTORY& playerGate);

/*!
 *    brief Function show information of completed games
 *
 *    param gameGate is object save games' information
 *
 *    return void
 */
void printGameInfo(GAME_FACTORY& gameGate);

/*!
 *    brief Function find player info and 2 players that is same level
 *
 *    param playerGate is object save players' information
 *
 *    return void
 */
void findPlayerInfo(PLAYER_FACTORY& playerGate);

/*!
 *    brief Function print list of players
 *
 *    param playerGate is object save players' information
 *
 *    return void
 */
void printPlayerList(PLAYER_FACTORY& playerGate);

/*******************************************************************************
 * Code
 ******************************************************************************/

/* main function */
int main()
{
    PLAYER_FACTORY playerGate;  /* object save players' information */
    GAME_FACTORY gameGate;      /* object save games' information */
    string choice = "0";        /* choice of menu */

    /* Load games and players' information */
    playerGate.loadPlayerFromFile("player.txt");
    gameGate.loadGameFromFile("game.txt");

    /* Print main menu */
    printMainMenu();
    cin.clear();
    getline(cin, choice);

    while (true)
    {
        switch (stoi(choice))
        {
            case 1: /* Play with other player */
            {
                system("cls");
                playWithOtherPlayer(playerGate, gameGate);

                /* Save information before exit program */
                playerGate.savePlayerToFile("player.txt");
                gameGate.saveGameToFile("game.txt");
                break;
            }
            case 2: /* Play with BOT */
            {
                system("cls");
                playWithBOT(playerGate, gameGate);

                /* Save information before exit program */
                playerGate.savePlayerToFile("player.txt");
                gameGate.saveGameToFile("game.txt");
                break;
            }
            case 3: /* Watch replay */
            {
                system("cls");
                printGameInfo(gameGate);
                break;
            }
            case 4: /* Players' information */
            {
                system("cls");
                playerInfo(playerGate);
                break;
            }
            case 5: /* Guide */
            {
                system("cls");
                printGuide();
                break;
            }
            case 6: /* Exit program */
            {
                return 0;
            }
            
        }
        system("cls");
        printMainMenu();
        cin.clear();
        getline(cin, choice);
        while (stoi(choice) < 1 || stoi(choice) > 6)
        {
            cout << "Invalid choice. Choose again: ";
            cin.clear();
            getline(cin, choice);
        }
    }
}

/*******************************************************************************
 * API
 ******************************************************************************/
 /*!
  *    brief Function setup all game for 2 players
  *
  *    param playerGate is object save players' information
  *    param gameGate is object save games' information
  *
  *    return void
  */
void playWithOtherPlayer(PLAYER_FACTORY &playerGate, GAME_FACTORY &gameGate)
{
    PLAYER* player1;
    PLAYER* player2;
    int playerIndex1 = IS_NEW_PLAYER;
    int playerIndex2 = IS_NEW_PLAYER;

    switch (printPlayWithOtherPlayer1(playerGate.getPlayerNumber()))
    {
        case 1: /* Choose an existing player */
        {
            /* Make player 1 */
            int playerIndex1 = IS_NOT_NEW_PLAYER;
            player1 = playerGate.makePlayer(playerIndex1);
            system("cls");
            switch (printPlayWithOtherPlayer2a(playerGate.getPlayerNumber()))
            {
                case 1: /* Choose an existing player */
                {
                    /* Make player 2 */
                    playerIndex2 = IS_NOT_NEW_PLAYER;
                    player2 = playerGate.makePlayer(playerIndex2);
                    while (player1->getPlayerName() == player2->getPlayerName()) /* Check player 1 == player 2*/
                    {
                        delete player2;
                        system("cls");
                        cout << "Cannot choose player 1!\n";
                        player2 = playerGate.makePlayer(playerIndex2);
                    }
                    /* Make game */
                    makeGame(player1, player2, playerIndex1, playerIndex2, playerGate, gameGate);
                    break;
                }
                case 2: /* Make a new player */
                {
                    /* Make player 2 */
                    playerIndex2 = IS_NEW_PLAYER;
                    player2 = playerGate.makePlayer(playerIndex2);
                    makeGame(player1, player2, playerIndex1, playerIndex2, playerGate, gameGate);
                    break;
                }
            }
            break;
        }
        case 2: /* Make a new player */
        {
            /* Make player 1 */
            playerIndex1 = IS_NEW_PLAYER;
            player1 = playerGate.makePlayer(playerIndex1);
            system("cls");
            switch (printPlayWithOtherPlayer2b(playerGate.getPlayerNumber()))
            {
                case 1: /* Choose an existing player */
                {
                    /* Make player 2 */
                    playerIndex2 = IS_NOT_NEW_PLAYER;
                    cin.ignore();
                    player2 = playerGate.makePlayer(playerIndex2);
                    /* Make game */
                    makeGame(player1, player2, playerIndex1, playerIndex2, playerGate, gameGate);
                    break;
                }
                case 2: /* Make a new player */
                {
                    /* Make player 2 */
                    playerIndex2 = IS_NEW_PLAYER;
                    cin.ignore();
                    player2 = playerGate.makePlayer(playerIndex2);
                    /* Make game */
                    makeGame(player1, player2, playerIndex1, playerIndex2, playerGate, gameGate);
                    break;
                }
            }
            break;
        }
        case 3: /* Back to MAIN MENU */
        {
            return;
        }
    }
}

/*!
 *    brief Function make a game for 2 players
 *
 *    param player1 is object save 1st player's info
 *    param player2 is object save 2nd player's info
 *    param playerIndex1 is index of player 1 in player list.
 *    playerIndex1 = -1 is new player
 *    param playerIndex2 is index of player 2 in player list.
 *    playerIndex2 = -1 is new player
 *
 *    return void
 */
void makeGame(PLAYER* &player1, PLAYER* &player2, int &playerIndex1, int& playerIndex2,
                PLAYER_FACTORY& playerGate, GAME_FACTORY& gameGate)
{
    string continueGame = YES;

    /* Create a game */
    while (YES == continueGame)
    {
        system("cls");
        GAME* game = gameGate.createGame(*player1, *player2);
        /* Save a game */
        gameGate.saveGame(*game);
        delete game;
        cout << "Replay game? (y/n): ";
        cin.clear();
        getline(cin, continueGame);
    }
    /* Save players */
    playerGate.savePlayer(*player1, playerIndex1);
    playerGate.savePlayer(*player2, playerIndex2);
    delete player1;
    delete player2;
}

/*!
 *    brief Function setup all game for BOT and player
 *
 *    param playerGate is object save players' information
 *    param gameGate is object save games' information
 *
 *    return void
 */
void playWithBOT(PLAYER_FACTORY& playerGate, GAME_FACTORY& gameGate)
{
    PLAYER* player;
    int playerIndex = IS_NEW_PLAYER;
    int botLevel = EASY;

    /* Choose bot level */
    botLevel = chooseBotLevel();

    /* Back to MAIN MENU */
    if (-1 == botLevel)
        return;

    /* Choose or create player */
    system("cls");
    switch (printPlayWithBOT(playerGate.getPlayerNumber()))
    {
        case 1: /* Choose an existing player */
        {
            /* Make player */
            playerIndex = IS_NOT_NEW_PLAYER;
            player = playerGate.makePlayer(playerIndex);
            system("cls");
            /* Make game */
            makeGame(player, playerIndex, playerGate, gameGate, botLevel);
            break;
        }
        case 2: /* Make a new player */
        {
            /* Make player */
            playerIndex = IS_NEW_PLAYER;
            player = playerGate.makePlayer(playerIndex);
            system("cls");
            /* Make game */
            makeGame(player, playerIndex, playerGate, gameGate, botLevel);
            break;
        }
        case 3: /* Back to MAIN MENU */
        {
            return;
        }
    }
}

/*!
 *    brief Function make a game for BOT and player
 *
 *    param player is object save player's info
 *    param playerIndex is index of player in player list.
 *    playerIndex = -1 is new player
 *    param botLevel is a level of the BOT (Easy, Normal, Hard)
 *
 *    return void
 */
void makeGame(PLAYER* &player, int& playerIndex, PLAYER_FACTORY& playerGate, GAME_FACTORY& gameGate, int botLevel)
{
    string continueGame = YES;

    /* Create a game */
    while (YES == continueGame)
    {
        system("cls");
        GAME* game = gameGate.createGame(*player, botLevel);
        /* Save a game */
        gameGate.saveGame(*game);
        delete game;
        cout << "Replay game? (y/n): ";
        cin.clear();
        getline(cin, continueGame);
    }
    /* Save players */
    playerGate.savePlayer(*player, playerIndex);
    delete player;
}

/*!
 *    brief Function find player info and 2 players that is same level
 *
 *    param playerGate is object save players' information
 *
 *    return void
 */
void findPlayerInfo(PLAYER_FACTORY& playerGate)
{
    string findName = "";
    string choice = "";
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Press name of player to find: ";
    getline(cin, findName);
    system("cls");
    playerGate.showPlayerInfo(findName);

    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "0. Back\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    getline(cin, choice);

    if ("" != choice)
        return;
}

/*!
 *    brief Function print list of players
 *
 *    param playerGate is object save players' information
 *
 *    return void
 */
void printPlayerList(PLAYER_FACTORY& playerGate)
{
    string choice = "";
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    playerGate.showPlayerList();

    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "0. Back\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    getline(cin, choice);

    if ("" != choice)
        return;
}

/*!
 *    brief Function show information of players
 *
 *    param playerGate is object save players' information
 *
 *    return void
 */
void playerInfo(PLAYER_FACTORY& playerGate)
{
    string choice = "";
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------PLAYER'S INFORMATION--------*\n";
    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "0. Back to MAIN MENU\n";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << "1. Find player\n";
    cout << "2. Print player list\n";
    getline(cin, choice);

    while ("0" != choice)
    {
        if ("1" == choice)
        {
            system("cls");
            findPlayerInfo(playerGate);
        }
        else if ("2" == choice)
        {
            system("cls");
            printPlayerList(playerGate);
        }

        system("cls");
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------PLAYER'S INFORMATION--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_RED);
        cout << "0. Back to MAIN MENU\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "1. Find player\n";
        cout << "2. Print player list\n";
        getline(cin, choice);
    }
}

/*!
 *    brief Function show information of completed games
 *
 *    param gameGate is object save games' information
 *
 *    return void
 */
void printGameInfo(GAME_FACTORY& gameGate)
{
    while (true)
    {
        string choice = "";
        /* Color of the console */
        HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

        system("cls");
        gameGate.showGameInfo();
        SetConsoleTextAttribute(consoleColor, COLOR_RED);
        cout << setw(10) << "0" << " Back to MAIN MENU\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);

        cout << "Press number to choice: ";
        getline(cin, choice);
        if ("0" == choice)
            return;

        while (stoi(choice) < 0 || stoi(choice) > 10)
        {
            cout << "Invalide choice. Choose agian: ";
            getline(cin, choice);
            if ("0" == choice)
                return;
        }
        system("cls");
        gameGate.showGameMove(stoi(choice)-1);
    }
}