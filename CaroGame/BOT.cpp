/*******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : ThuanDV12
Content      : Create a C++ console game Caro (10x10).
******************************************************************************/
#include "BOT.h"

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
 *    brief Function calculate point follow count of symbol
 *
 *    param botCount is number moves of bot
 *    param c_botCount is number continue moves of bot
 *    param playerCount is number movers of player
 *    param c_playerCount is number continue moves of player
 *
 *    return point follow count of symbol
 */
int scoreCalculate(int botCount, int c_botCount, int playerCount, int c_playerCount)
{
    int score = 0;

    /* 4 moves in a row */
    if (WIN_CONDITION == botCount)
        score += WIN_POINT;
    if (WIN_CONDITION == playerCount)
        score += (LOSE_POINT);
    /* 3 continuous moves in a row */
    if (botCount == (WIN_CONDITION - 1) && playerCount == 0 && botCount == c_botCount)
        score += WIN_POINT / 10;
    if (playerCount == (WIN_CONDITION - 1) && botCount == 0 && playerCount == c_playerCount)
        score += LOSE_POINT / 10;
    /* 3 moves in a row */
    if (botCount == (WIN_CONDITION - 1) && playerCount == 0)
        score += WIN_POINT / 100;
    if (playerCount == (WIN_CONDITION - 1) && botCount == 0)
        score += LOSE_POINT / 100;
    /* 2 moves in a row */
    if (botCount == (WIN_CONDITION - 2) && playerCount == 0)
        score += WIN_POINT / 1000;
    if (playerCount == (WIN_CONDITION - 2) && botCount == 0)
        score += LOSE_POINT / 1000;

    if (botCount == (WIN_CONDITION - 2))
        score += WIN_POINT / 5000;
    if (playerCount == (WIN_CONDITION - 2))
        score += LOSE_POINT / 5000;
    /* 1 move */
    if (botCount == (WIN_CONDITION - 3))
        score += WIN_POINT / 10000;
    if (playerCount == (WIN_CONDITION - 3))
        score += LOSE_POINT / 10000;

    return score;
}

/*!
 *    brief Function to evaluate the board for the Minimax algorithm
 *
 *    param board[][BOARD_SIZE] is board status
 *    param symbol is symbol of bot
 *    param depth is depth of minimax algorithm
 *
 *    return relative value of current board
 */
int evaluate(char board[][BOARD_SIZE], char symbol, int depth)
{
    int score = 0;

    /* Horizontal evaluation */
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j <= BOARD_SIZE - WIN_CONDITION; j++)
        {
            int botCount = 0;
            int c_botCount = 0;
            int playerCount = 0;
            int c_playerCount = 0;

            for (int k = 0; k < WIN_CONDITION; k++)
            {
                if (board[i][j + k] == symbol)
                {
                    botCount++;
                    c_botCount++;
                }
                else if (board[i][j + k] != EMPTY)
                {
                    playerCount++;
                    c_playerCount++;
                }
                else if ((0 != k) && (WIN_CONDITION-1 != k))
                {
                    c_playerCount = 0;
                    c_botCount = 0;
                }
            }
            score += scoreCalculate(botCount, c_botCount, playerCount, c_playerCount);
        }
    }

    /* Vertical evaluation */
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        for (int i = 0; i <= BOARD_SIZE - WIN_CONDITION; i++)
        {
            int botCount = 0;
            int c_botCount = 0;
            int playerCount = 0;
            int c_playerCount = 0;

            for (int k = 0; k < WIN_CONDITION; k++)
            {
                if (board[i + k][j] == symbol)
                {
                    botCount++;
                    c_botCount++;
                }
                else if (board[i + k][j] != EMPTY)
                {
                    playerCount++;
                    c_playerCount++;
                }
                else if ((0 != k) && (WIN_CONDITION-1 != k))
                {
                    c_playerCount = 0;
                    c_botCount = 0;
                }
            }
            score += scoreCalculate(botCount, c_botCount, playerCount, c_playerCount);
        }
    }

    /* Diagonal evaluation (top-left to bottom-right) */
    for (int i = 0; i <= BOARD_SIZE - WIN_CONDITION; i++)
    {
        for (int j = 0; j <= BOARD_SIZE - WIN_CONDITION; j++)
        {
            int botCount = 0;
            int c_botCount = 0;
            int playerCount = 0;
            int c_playerCount = 0;

            for (int k = 0; k < WIN_CONDITION; k++)
            {
                if (board[i + k][j + k] == symbol)
                {
                    botCount++;
                    c_botCount++;
                }
                else if (board[i + k][j + k] != EMPTY)
                {
                    playerCount++;
                    c_playerCount++;
                }
                else if ((0 != k) && (WIN_CONDITION-1 != k))
                {
                    c_playerCount = 0;
                    c_botCount = 0;
                }
            }
            score += scoreCalculate(botCount, c_botCount, playerCount, c_playerCount);
        }
    }

    /* Diagonal evaluation (top-right to bottom-left) */
    for (int i = 0; i <= BOARD_SIZE - WIN_CONDITION; i++)
    {
        for (int j = BOARD_SIZE - 1; j >= WIN_CONDITION - 1; j--)
        {
            int botCount = 0;
            int c_botCount = 0;
            int playerCount = 0;
            int c_playerCount = 0;

            for (int k = 0; k < WIN_CONDITION; k++)
            {
                if (board[i + k][j - k] == symbol)
                {
                    botCount++;
                    c_botCount++;
                }
                else if (board[i + k][j - k] != EMPTY)
                {
                    playerCount++;
                    c_playerCount++;
                }
                else if ((0 != k) && (WIN_CONDITION - 1 != k))
                {
                    c_playerCount = 0;
                    c_botCount = 0;
                }
            }
            score += scoreCalculate(botCount, c_botCount, playerCount, c_playerCount);
        }
    }

    return static_cast<int>(score * pow(10, depth));
}

/*!
 *    brief Function check around cells is empty or not
 *
 *    param board[][BOARD_SIZE] is board status
 *    param i is row index of this cell
 *    param j is column index of this cell
 *
 *    return true if all around cells is empty and vice versa
 */
bool emptySymbolAround(char board[][BOARD_SIZE], int i, int j)
{
    int iLess = i - 1;
    int iMore = i + 1;
    int jLess = j - 1;
    int jMore = j + 1;

    if (0 > iLess) iLess = 0;
    if (BOARD_SIZE <= iMore) iMore = BOARD_SIZE - 1;
    if (0 > jLess) jLess = 0;
    if (BOARD_SIZE <= jMore) jMore = BOARD_SIZE - 1;

    for (int i = iLess; i <= iMore; i++)
    {
        for (int j = jLess; j <= jMore; j++)
        {
            if (EMPTY != board[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

/*!
 *    brief Minimax function with alpha-beta pruning
 *
 *    param board[][BOARD_SIZE] is board status
 *    param depth is depth of minimax algorithm
 *    param maximizingPlayer is true if this Node is MAX and vice versa
 *    param alpha, beta is alpha, beta pruning factor
 *    param currentMove is coordinate of current move
 *    param symbol is symbol of bot
 *
 *    return relative value of current board
 */
int miniMax(char board[][BOARD_SIZE], int depth, bool maximizingPlayer, int alpha, int beta,
    pair<int, int> currentMove, char symbol)
{
    char opponentSymbol = (PLAYER1_SYMBOL == symbol) ? PLAYER2_SYMBOL : PLAYER1_SYMBOL;
    /* Check leaf node in game tree or depth == 0 */
    if (depth == 0 || checkWin(board, currentMove, symbol) || checkWin(board, currentMove, opponentSymbol))
    {
        return evaluate(board, symbol, depth);
    }

    /* If current node is MAX */
    if (maximizingPlayer)
    {
        int bestVal = INT_MIN;
        /* Recurse all child node */
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (isValidMove(board, { i, j }))
                {
                    if (!emptySymbolAround(board, i, j))
                    {
                        /* Assume bot is player 1 */
                        board[i][j] = symbol;
                        /* Caculate move value of child node, child node is MIN */
                        int value = miniMax(board, depth - 1, false, alpha, beta, { i, j }, symbol);
                        board[i][j] = EMPTY;
                        bestVal = max(bestVal, value);
                        /* Alpha Beta pruning */
                        alpha = max(alpha, value);
                        if (beta <= alpha)
                            break;
                    }
                }
            }
        }
        return bestVal;
    }
    else /* If current node is MIN */
    {
        int bestVal = INT_MAX;
        /* Recurse all child node */
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (isValidMove(board, {i, j}))
                {
                    if (!emptySymbolAround(board, i, j))
                    {
                        /* Assume opponent is player 2 */
                        board[i][j] = opponentSymbol;
                        /* Caculate move value of child node, child node is MAX */
                        int value = miniMax(board, depth - 1, true, alpha, beta, { i, j }, symbol);
                        board[i][j] = EMPTY;
                        bestVal = min(bestVal, value);
                        /* Alpha Beta pruning */
                        beta = min(beta, value);
                        if (beta <= alpha)
                            break;
                    }
                }
            }
        }
        return bestVal;
    }
}

/*!
 *    brief Function for the bot to make a move
 *
 *    param board[][BOARD_SIZE] is board status
 *    param symbol is symbol of bot
 *    param botLevel is depth of minimax algorithm.
 *    The more depth, the more level
 *
 *    return relative value of current board
 */
pair<int, int> BOT::findBestMove(char board[][BOARD_SIZE], char symbol, int botLevel)
{
    int bestVal = INT_MIN;      /* Best value of move */
    pair<int, int> bestMove{ 4,5 };    /* Best move */

    /* Check all move */
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (isValidMove(board, { i, j }))
            {
                if (!emptySymbolAround(board, i, j))
                {
                    board[i][j] = symbol;
                    /* Caculate move value of child node, child node is MIN */
                    int value = miniMax(board, botLevel, false, INT_MIN, INT_MAX, { i, j }, symbol);
                    board[i][j] = EMPTY;
                    /* Current node is MAX */
                    if (value > bestVal)
                    {
                        bestVal = value;
                        bestMove = { i, j };
                    }
                }
            } 
        }
    }

    return bestMove;
}