/*******************************************************************************
Project name : CPP.MockProject01.P001
Session      : Caro Game
Version      : 1.0
Author       : ThuanDV12
Content      : Create a C++ console game Caro (10x10).
******************************************************************************/
#include "player.h"

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
 *    brief Function update score of players
 *
 *    param score is score that player gain in game
 *
 *    return void
 */
void PLAYER::updateScore(int score)
{
    if (WIN_POINT == score)
    {
        m_winNum++;
    }
    else if(WIN_POINT == score)
    {
        m_drawNum++;
    }
    else
    {
        m_loseNum++;
    }
    m_score += score;
}

/*!
 *    brief Function get name of player
 *
 *    return name of player
 */
string PLAYER::getPlayerName()
{
    return m_name;
}

/*!
 *    brief Function overloading operator = for class PLAYER
 *
 *    param player is source player
 *
 *    return destination player
 */
PLAYER PLAYER::operator=(PLAYER player)
{
    m_name = player.m_name;
    m_winNum = player.m_winNum;
    m_drawNum = player.m_drawNum;
    m_loseNum = player.m_loseNum;
    m_score = player.m_score;

    return *this;
}

/*!
 *    brief Function make player for game
 *
 *    param playerIndex is index of player in list
 *
 *    return maked player
 */
PLAYER* PLAYER_FACTORY::makePlayer(int &playerIndex)
{
    PLAYER* player = new PLAYER;
    bool found = true;
    string name;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    if (IS_NEW_PLAYER == playerIndex) /* Create a new player */
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------CREATE A NEW PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        cout << "Press name of player: ";
        cin.clear();
        getline(cin, name);

        /* Check until name of new player does not exist */
        while (true == found)
        {
            found = false;
            for (int i = 0; i < m_numPlayer; i++)
            {
                if (name == m_player[i].m_name)
                {
                    found = true;
                    break;
                }
            }

            if (true == found)
            {
                cout << "This name is exist.\n";
                cout << "Press name of player: ";
                cin.clear();
                getline(cin, name);
            }
        }

        cout << "Making a new player with name: " << name << endl;
        player->m_name = name;
    }
    else /* Choose an existing player */
    {
        SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
        cout << "*--------CHOOSE AN EXISTING PLAYER--------*\n";
        SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
        /* Print name of existing player */
        for (int i = 0; i < m_numPlayer; i++)
        {
            cout << setw(20) << m_player[i].m_name;
            /* Print 4 players each line */
            if ((i + 1) % 4 == 0) cout << endl;
        }
        cout << endl;

        cout << "Press name of player: ";
        cin.clear();
        getline(cin, name);

        found = false;
        /* Check until find existing player */
        while (false == found)
        {
            for (int i = 0; i < m_numPlayer; i++)
            {
                if (name == m_player[i].m_name)
                {
                    playerIndex = i;
                    found = true;
                    break;
                }
            }

            if(false == found)
            {
                cout << "That name is not correct. Choose again: ";
                cin.clear();
                getline(cin, name);
            }
        }
        cout << "You chose player " << name << endl;
        *player = m_player[playerIndex];
    }
    
    return player;
}

/*!
 *    brief Function save player's info
 *
 *    param player is player that will be saved
 *    param playerIndex is index of player in list
 * 
 *    return void
 */
void PLAYER_FACTORY::savePlayer(PLAYER player, int playerIndex)
{
    if (IS_NEW_PLAYER == playerIndex)
    {
        m_player.push_back(player);
        /* Increase number of player */
        m_numPlayer++;
    }
    else
    {
        m_player.erase(m_player.begin() + playerIndex);
        m_player.insert(m_player.begin() + playerIndex, player);
    }
}

/*!
 *    brief Function get number of player
 *
 *    return number of player
 */
int PLAYER_FACTORY::getPlayerNumber()
{
    return m_numPlayer;
}

/*!
 *    brief Function load information of players
 *
 *    param fileName is name of file where stores players' info
 *
 *    return void
 */
void PLAYER_FACTORY::loadPlayerFromFile(const string& fileName)
{
    string inputStr;

    ifstream inputFile{ fileName };
    /* Check file is open successfully */
    if (!inputFile)
    {
        cout << "Error when loading player info!\n";
        return;
    }

    /* While there's still stuff left to read */
    /* Each line is 1 player information */
    while (getline(inputFile, inputStr))
    {
        PLAYER player;
        string temp;
        stringstream ss(inputStr);

        ss >> temp;
        player.m_winNum = stoi(temp);
        ss >> temp;
        player.m_loseNum = stoi(temp);
        ss >> temp;
        player.m_drawNum = stoi(temp);
        ss >> temp;
        player.m_score = stoi(temp);
        ss >> temp;
        getline(ss, player.m_name);
        player.m_name = temp + player.m_name;

        m_player.push_back(player);
        m_numPlayer++;
    }

    /* Close file */
    inputFile.close();
}

/*!
 *    brief Function get score of player
 *
 *    return score of player
 */
int PLAYER::getScore()
{
    return m_score;
}

/*!
 *    brief Function compare score of 2 players
 *
 *    param player1 is 1st player
 *    param player2 is 2nd player
 *
 *    return true if 1st player's score is greater than 2nd player's score and vice versa
 */
bool comparePlayerScore(PLAYER player1, PLAYER player2)
{
    return (player1.getScore() > player2.getScore());
}

/*!
 *    brief Function save information of players
 *
 *    param fileName is name of file where stores players' info
 *
 *    return void
 */
void PLAYER_FACTORY::savePlayerToFile(const string &fileName)
{
    /* Sort player from low score to high score */
    sort(m_player.begin(), m_player.end(), comparePlayerScore);

    /* Open file */
    ofstream outputFile{ fileName };

    /* Check file is open successfully */
    if (!outputFile)
    {
        cout << "Error when saving player info!\n";
        return;
    }
    
    /* Save player's information to file */
    for (int i = 0; i < m_numPlayer; i++)
    {
        outputFile << to_string(m_player[i].m_winNum) + " " + to_string(m_player[i].m_loseNum) + " "
                      + to_string(m_player[i].m_drawNum) + " " + to_string(m_player[i].m_score) + " "
                      + m_player[i].m_name << '\n';
    }

    /* Close file */
    outputFile.close();
}

/*!
 *    brief Function show list of players
 *
 *    return void
 */
void PLAYER_FACTORY::showPlayerList()
{
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
    cout << "*--------PLAYER'S INFORMATION--------*\n";
    SetConsoleTextAttribute(consoleColor, COLOR_GREEN);
    cout << setw(10) << "NO." << setw(25) << "NAME" << setw(10) << "WIN"
        << setw(10) << "DRAW" << setw(10) << "LOSE" << setw(10) << "SCORE" << endl;
    SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
    for (int i = 0; i < m_numPlayer; i++)
    {
        cout << setw(10) << i+1 << setw(25) << m_player[i].m_name << setw(10) << m_player[i].m_winNum
            << setw(10) << m_player[i].m_drawNum << setw(10) << m_player[i].m_loseNum
            << setw(10) << m_player[i].m_score << endl;
    }
}

/*!
 *    brief Function show information of player
 *
 *    param namePlayer is name of player
 *
 *    return void
 */
void PLAYER_FACTORY::showPlayerInfo(string namePlayer)
{
    bool found = false;
    /* Color of the console */
    HANDLE consoleColor = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < m_numPlayer; i++)
    {
        if (namePlayer == m_player[i].m_name)
        {
            SetConsoleTextAttribute(consoleColor, COLOR_CYAN);
            cout << "*--------PLAYER'S INFORMATION--------*\n";
            SetConsoleTextAttribute(consoleColor, COLOR_GREEN);
            cout << setw(10) << "NO." << setw(25) << "NAME" << setw(10) << "WIN"
                << setw(10) << "DRAW" << setw(10) << "LOSE" << setw(10) << "SCORE" << endl;
            SetConsoleTextAttribute(consoleColor, COLOR_WHITE);
            if (0 == i)
            {
                for (int j = 0; j < 3; j++)
                {
                    cout << setw(10) << j + 1 << setw(25) << m_player[j].m_name << setw(10) << m_player[j].m_winNum
                        << setw(10) << m_player[j].m_drawNum << setw(10) << m_player[j].m_loseNum
                        << setw(10) << m_player[j].m_score << endl;
                }
            }
            else if (m_numPlayer - 1 == i)
            {
                for (int j = m_numPlayer - 3; j < m_numPlayer; j++)
                {
                    cout << setw(10) << j + 1 << setw(25) << m_player[j].m_name << setw(10) << m_player[j].m_winNum
                        << setw(10) << m_player[j].m_drawNum << setw(10) << m_player[j].m_loseNum
                        << setw(10) << m_player[j].m_score << endl;
                }
            }
            else
            {
                for (int j = i - 1; j < i + 2; j++)
                {
                    cout << setw(10) << j + 1 << setw(25) << m_player[j].m_name << setw(10) << m_player[j].m_winNum
                        << setw(10) << m_player[j].m_drawNum << setw(10) << m_player[j].m_loseNum
                        << setw(10) << m_player[j].m_score << endl;
                }
            }
            found = true;
        }
    }

    if (false == found)
    {
        cout << "Cannot find the player\n";
    }
}