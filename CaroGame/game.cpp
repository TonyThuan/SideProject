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
 *    brief Function save game info
 *
 *    param game is game's info that will be saved
 *
 *    return void
 */
void GAME_FACTORY::saveGame(GAME game)
{
    /* Only save 10 latest game */
    if (SAVED_GAME == m_numGame)
    {
        m_game.erase(m_game.begin());
    }
    else
    {
        /* Increase number of game */
        m_numGame++;
    }
    m_game.push_back(game);
}

/*!
 *    brief Function print board of game
 *
 *    param board[][BOARD_SIZE] is board status
 *    param player1Turn is true if current turn is 1st player's turn and vice versa
 *    param currentMove is coordinate of current move
 *    param player1name is 1st player name
 *    param player2name is 2nd player name
 *
 *    return void
 */
void printBoard(char board[][BOARD_SIZE], bool player1Turn, pair<int, int> currentMove, string player1name, string player2name)
{
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    /* Print 1st row */
    cout << "=> ";
    SetConsoleTextAttribute(consoleColor, COLOR_RED);
    cout << "Player 1 (" + player1name + ") = X";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << ", ";
    SetConsoleTextAttribute(consoleColor, COLOR_GREEN);
    cout << "Player 2 (" + player2name + ") = O";
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    cout << ":\n\n";

    /* Print 2nd row */
    cout << "    0";
    for (int i = 1; i < BOARD_SIZE; i++)
    {
        cout << "   " << i%10;
    }
    cout << endl;

    /* Print caro table */
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        /* Print rơw border */
        cout << "  |";
        for (int k = 0; k < BOARD_SIZE; k++)
        {
            cout << "---|";
        }
        cout << endl;

        /* Print content */
        cout << i%10 << " |";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (i == currentMove.first && j == currentMove.second)
            {
                SetConsoleTextAttribute(consoleColor, COLOR_YELLOW);
                cout << " " << board[i][j];
                SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
            }
            else if (PLAYER1_SYMBOL == board[i][j])
            {
                SetConsoleTextAttribute(consoleColor, COLOR_RED);
                cout << " " << board[i][j];
                SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
            }
            else if (PLAYER2_SYMBOL == board[i][j])
            {
                SetConsoleTextAttribute(consoleColor, COLOR_GREEN);
                cout << " " << board[i][j];
                SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
            }
            else
            {
                cout << " " << board[i][j];
            }
            cout << " |";
        }
        cout << endl;
    }

    /* Print last border row */
    cout << "  |";
    for (int k = 0; k < BOARD_SIZE; k++)
    {
        cout << "---|";
    }
    cout << endl << endl;

    if (player1Turn)
    {
        SetConsoleTextAttribute(consoleColor, COLOR_RED);
        cout << "Player 1's turn: ";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    }
    else
    {
        SetConsoleTextAttribute(consoleColor, COLOR_GREEN);
        cout << "Player 2's turn: ";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    }
}

/*!
 *    brief Function check validation of move
 *
 *    param board[][BOARD_SIZE] is board status
 *    param currentMove is coordinate of current move
 *
 *    return true if current move is valid move and vice versa
 */
bool isValidMove(char board[][BOARD_SIZE], pair<int, int> currentMove)
{
    /* Check current location is valid */
    return (currentMove.first >= 0 && currentMove.first < BOARD_SIZE && currentMove.second >= 0
        && currentMove.second < BOARD_SIZE && board[currentMove.first][currentMove.second] == EMPTY);
}

/*!
 *    brief Function check winning condition
 *
 *    param board[][BOARD_SIZE] is board status
 *    param currentMove is coordinate of current move
 *    param symbol is symbol of current player
 *
 *    return true if winning condition happend and vice versa
 */
bool checkWin(char board[][BOARD_SIZE], pair<int, int> currentMove, char symbol)
{
    int count = 0;
    int row = currentMove.first;
    int column = currentMove.second;

    /* Check 4 symbol vertically */
    for (int i = row - (WIN_CONDITION - 1); i <= row + (WIN_CONDITION - 1); i++)
    {
        if (i >= 0 && i < BOARD_SIZE && board[i][column] == symbol)
        {
            count++;
            if (count >= WIN_CONDITION) return true;
        }
        else
        {
            count = 0;
        }
    }

    /* Check 4 symbol horizontally */
    count = 0;
    for (int j = column - (WIN_CONDITION-1); j <= column + (WIN_CONDITION-1); j++)
    {
        if (j >= 0 && j < BOARD_SIZE && board[row][j] == symbol)
        {
            count++;
            if (count >= WIN_CONDITION) return true;
        }
        else
        {
            count = 0;
        }
    }

    /* Check 4 symbol diagonally (top-left to bottom-right) */
    count = 0;
    for (int i = row - (WIN_CONDITION - 1), j = column - (WIN_CONDITION - 1);
        i <= row + (WIN_CONDITION - 1) && j <= column + (WIN_CONDITION - 1); i++, j++)
    {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] == symbol)
        {
            count++;
            if (count >= WIN_CONDITION) return true;
        }
        else
        {
            count = 0;
        }
    }

    /* Check 4 symbol diagonally (top-right to bottom-left) */
    count = 0;
    for (int i = row - (WIN_CONDITION - 1), j = column + (WIN_CONDITION - 1);
        i <= row + (WIN_CONDITION - 1) && j >= column - (WIN_CONDITION - 1); i++, j--)
    {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] == symbol)
        {
            count++;
            if (count >= WIN_CONDITION) return true;
        }
        else
        {
            count = 0;
        }
    }

    return false;
}

/*!
 *    brief Function check board is full
 *
 *    param board[][BOARD_SIZE] is board status
 *
 *    return true if board is full and vice versa
 */
bool isBoardFull(char board[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (EMPTY == board[i][j]) return false;
        }
    }
    return true;
}

/*!
 *    brief Function input current move that user press from keyboard
 *
 *    param currentMove stores coordinate of current move
 *
 *    return void
 */
void inputCurrentMove(pair<int, int> &currentMove)
{
    string str;

    /* Read whole line into string */
    cin.clear();
    getline(cin, str);

    /* Read to row and column */
    stringstream ss(str);
    ss >> str;
    currentMove.first = stoi(str);
    ss >> str;
    currentMove.second = stoi(str);
}

/*!
 *    brief Function create care game for 2 players
 *
 *    param player1 is 1st player
 *    param player2 is 2nd player
 *
 *    return created game's info
 */
GAME* GAME_FACTORY::createGame(PLAYER& player1, PLAYER& player2)
{
    GAME* game = new GAME;
    char currentBoard[BOARD_SIZE][BOARD_SIZE] = { };
    bool player1Turn = true;
    bool gameOver = false;
    pair<int, int> currentMove{ -1, -1 }; /*  Move status: 1st element is row, 2nd element is column */

    game->m_player1.first = player1.m_name;
    game->m_player2.first = player2.m_name;

    /* Initialize empty element for board */
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            currentBoard[i][j] = EMPTY;
        }
    }

    /* Check game over condition */
    while (!gameOver)
    {
        /* Current symbol */
        char symbol = player1Turn ? PLAYER1_SYMBOL : PLAYER2_SYMBOL;

        /* Print board game */
        system("cls");
        printBoard(currentBoard, player1Turn, currentMove, game->m_player1.first, game->m_player2.first);
        
        /* Read row and column of move */
        inputCurrentMove(currentMove);

        /* Check valid move */
        if (isValidMove(currentBoard, currentMove))
        {
            /* Put current move to board */
            currentBoard[currentMove.first][currentMove.second] = symbol;

            /* Check win condition */
            if (checkWin(currentBoard, currentMove, symbol))
            {
                system("cls");
                printBoard(currentBoard, player1Turn, currentMove, game->m_player1.first, game->m_player2.first);
                
                /* Game over: Update player's score */
                if (player1Turn)
                {
                    cout << "\n=> Player 1 (" + game->m_player1.first + ") wins!\n\n";
                    player1.updateScore(WIN_POINT);
                    player2.updateScore(LOSE_POINT);
                    game->m_player1.second = WIN_POINT;
                    game->m_player2.second = LOSE_POINT;
                }
                else
                {
                    cout << "\n=> Player 2 (" + game->m_player2.first + ") wins!\n\n";
                    player1.updateScore(LOSE_POINT);
                    player2.updateScore(WIN_POINT);
                    game->m_player1.second = LOSE_POINT;
                    game->m_player2.second = WIN_POINT;
                }
                gameOver = true;
            }
            else if (isBoardFull(currentBoard)) /* If board is full then game is draw */
            {
                system("cls");
                printBoard(currentBoard, player1Turn, currentMove, game->m_player1.first, game->m_player2.first);
                cout << "It's a draw!\n" << endl;

                /* Game over: Update player's score */
                player1.updateScore(DRAW_POINT);
                player2.updateScore(DRAW_POINT);
                game->m_player1.second = DRAW_POINT;
                game->m_player2.second = DRAW_POINT;
                gameOver = true;
            }
            player1Turn = !player1Turn;
            /* Save move status */
            game->m_moveStatus.push_back(currentMove);
        }
        else
        {
            cout << "Invalid move! Try again: " << endl;
        }
    }

    return game;
}

/*!
 *    brief Function create care game for player and bot
 *
 *    param player is player
 *    param botLevel is level of bot
 *
 *    return created game's info
 */
GAME* GAME_FACTORY::createGame(PLAYER& player, int botLevel)
{
    GAME* game = new GAME;
    char currentBoard[BOARD_SIZE][BOARD_SIZE] = { };
    bool player1Turn = true;
    bool gameOver = false;
    pair<int, int> currentMove{ -1, -1 }; /*  Move status: 1st element is row, 2nd element is column */
    string level = "EASY";
    BOT bot;

    /* Named player and bot in game */
    if (EASY == botLevel)
        level = "EASY";
    else if (NORMAL == botLevel)
        level = "NORMAL";
    else
        level = "HARD";
    game->m_player1.first = "BOT-" + level;
    game->m_player2.first = player.m_name;

    /* Initialize empty element for board */
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            currentBoard[i][j] = EMPTY;
        }
    }

    /* Check game over condition */
    while (!gameOver)
    {
        /* Current symbol */
        char symbol = player1Turn ? PLAYER1_SYMBOL : PLAYER2_SYMBOL;

        /* Print board game */
        system("cls");
        printBoard(currentBoard, player1Turn, currentMove, game->m_player1.first, game->m_player2.first);

        if (player1Turn) /* BOT turn */
        {
            currentMove = bot.findBestMove(currentBoard, PLAYER1_SYMBOL, botLevel);
        }
        else /* Player turn */
        {
            /* Read row and column of move */
            inputCurrentMove(currentMove);
        }

        /* Check valid move */
        if (isValidMove(currentBoard, currentMove))
        {
            /* Put current move to board */
            currentBoard[currentMove.first][currentMove.second] = symbol;

            /* Check win condition */
            if (checkWin(currentBoard, currentMove, symbol))
            {
                system("cls");
                printBoard(currentBoard, player1Turn, currentMove, game->m_player1.first, game->m_player2.first);

                /* Game over: Update player's score */
                if (player1Turn)
                {
                    cout << "\n=> Player 1 (" + game->m_player1.first + ") wins!\n\n";
                    player.updateScore(LOSE_POINT);
                    game->m_player1.second = WIN_POINT;
                    game->m_player2.second = LOSE_POINT;
                }
                else
                {
                    cout << "\n=> Player 2 (" + game->m_player2.first + ") wins!\n\n";
                    player.updateScore(WIN_POINT);
                    game->m_player1.second = LOSE_POINT;
                    game->m_player2.second = WIN_POINT;
                }
                gameOver = true;
            }
            else if (isBoardFull(currentBoard)) /* If board is full then game is draw */
            {
                system("cls");
                printBoard(currentBoard, player1Turn, currentMove, game->m_player1.first, game->m_player2.first);
                cout << "It's a draw!" << endl;

                /* Game over: Update player's score */
                player.updateScore(DRAW_POINT);
                game->m_player1.second = DRAW_POINT;
                game->m_player2.second = DRAW_POINT;
                gameOver = true;
            }
            player1Turn = !player1Turn;
            /* Save move status */
            game->m_moveStatus.push_back(currentMove);
        }
        else
        {
            cout << "Invalid move! Try again: " << endl;
        }
    }

    return game;
}

/*!
 *    brief Function load games' info from file
 *
 *    param fileName is name of stored file
 *
 *    return void
 */
void GAME_FACTORY::loadGameFromFile(const string& fileName)
{
    string inputStr;

    ifstream inputFile{ fileName };
    /* Check file is open successfully */
    if (!inputFile)
    {
        cout << "Error when loading game info!\n";
        return;
    }

    /* While there's still stuff left to read */
    /* Each line is 1 player information */
    while (getline(inputFile, inputStr))
    {
        GAME game;
        string temp;
        stringstream ss(inputStr);

        ss >> temp;
        game.m_player1.second = stoi(temp);
        getline(ss, temp);
        game.m_player1.first = temp;
        ss.str("");
        ss.clear();

        getline(inputFile, inputStr);
        ss << inputStr;
        ss >> temp;
        game.m_player2.second = stoi(temp);
        getline(ss, temp);
        game.m_player2.first = temp;
        ss.str("");
        ss.clear();

        getline(inputFile, inputStr);
        ss << inputStr;
        while (ss >> temp)
        {
            string temp2;
            ss >> temp2;
            game.m_moveStatus.push_back({ stoi(temp), stoi(temp2) });
        }

        m_game.push_back(game);
        m_numGame++;
    }

    /* Close file */
    inputFile.close();
}

/*!
 *    brief Function save games' info from file
 *
 *    param fileName is name of stored file
 *
 *    return void
 */
void GAME_FACTORY::saveGameToFile(const string& fileName)
{
    /* Open file */
    ofstream outputFile{ fileName };

    /* Check file is open successfully */
    if (!outputFile)
    {
        cout << "Error when saving game info!\n";
        return;
    }

    /* Save game's information to file */
    for (int i = 0; i < m_numGame; i++)
    {
        outputFile << to_string(m_game[i].m_player1.second) + " " + m_game[i].m_player1.first + "\n";
        outputFile << to_string(m_game[i].m_player2.second) + " " + m_game[i].m_player2.first + "\n";

        outputFile << to_string(m_game[i].m_moveStatus[0].first) + " " +
            to_string(m_game[i].m_moveStatus[0].second);
        int statusNum = m_game[i].m_moveStatus.size();
        for (int j = 1; j < statusNum; j++)
        {
            outputFile << " " + to_string(m_game[i].m_moveStatus[j].first) + " " +
                to_string(m_game[i].m_moveStatus[j].second);
        }
        outputFile << endl;
    }

    /* Close file */
    outputFile.close();
}

/*!
 *    brief Function print games' info
 *
 *    return void
 */
void GAME_FACTORY::showGameInfo()
{
    string winner;
    string draw = "";
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------GAME'S INFORMATION--------*\n";
    SetConsoleTextAttribute(consoleColor, COLOR_GREEN);
    cout << setw(10) << "NO." << setw(10) << "GAME" << setw(25) << "PLAYER 1"
        << setw(25) << "PLAYER 2" << setw(25) << "WINNER" << setw(10) << "DRAW" << endl;
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    for (int i = 0; i < m_numGame; i++)
    {
        if (m_game[i].m_player1.second > m_game[i].m_player2.second)
        {
            winner = m_game[i].m_player1.first;
        }
        else if (m_game[i].m_player1.second < m_game[i].m_player2.second)
        {
            winner = m_game[i].m_player2.first;
        }
        else
        {
            winner = "";
            draw = "YES";
        }
        cout << setw(10) << i+1 << setw(10) << "GAME " + to_string(i+1) << setw(25) << m_game[i].m_player1.first
            << setw(25) << m_game[i].m_player2.first << setw(25) << winner << setw(10) << draw << endl;
    }
}

/*!
 *    brief Function show completed games' moves
 *
 *    param fileName is name of stored file
 *
 *    return void
 */
void GAME_FACTORY::showGameMove(int index)
{
    bool player1Turn = true;
    char board[BOARD_SIZE][BOARD_SIZE] = { };
    int size = m_game[index].m_moveStatus.size();
    pair<int, int> currentMove{ -1, -1 };
    char symbol = EMPTY;
    string choice = "";

    /* Initialize empty element for board */
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = EMPTY;
        }
    }

    /* Print moves of game */
    for (int i = 0; i < size; i++)
    {
        char symbol = player1Turn ? PLAYER1_SYMBOL : PLAYER2_SYMBOL;

        currentMove = { m_game[index].m_moveStatus[i].first, m_game[index].m_moveStatus[i].second };
        board[m_game[index].m_moveStatus[i].first][m_game[index].m_moveStatus[i].second] = symbol;
        printBoard(board, player1Turn, currentMove, m_game[index].m_player1.first, m_game[index].m_player2.first);
        player1Turn = !player1Turn;

        cout << "\nPress n (NEXT) - e (EXIT)\n";
        getline(cin, choice);

        if("e" == choice)
        {
            return;
        }
        system("cls");
    }
}