#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <vector>

class TicTacToe
{
private:
    std::vector<std::vector<char>> board;

public:
    TicTacToe()
    {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    }

    void printBoard()
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (col < 2) std::cout << board[row][col] << "|";
                else std::cout << board[row][col];
            }
            if(row < 2) std::cout << "\n-----\n";
        }
    }

    bool isValidMove(int row, int col)
    {
        if (0 > row || row > 2 || 0 > col || col > 2) 
        {
            system("cls");
            std::cout << "INVALID MOVE\n";
            return false;
        }
        if (board[row][col] != ' ')
        {
            system("cls");
            std::cout << "INVALID MOVE\n";
            return false;
        }
        else
        {
            system("cls");
            return true;
        }
    }

    void makeMove(int row, int col, char player)
    {
        board[row][col] = player;
    }

    bool checkWin(char player)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        }
        for (int i = 0; i < 3; i++)
        {
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
        else return false;
    }

    bool checkTie()
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (board[row][col] == ' ') return false;
            }
        }
        return true;
    }
};

int main()
{
    TicTacToe Game;
    bool win = false, valid = false, tie = false;
    int turn = 1, row, col, imput;
    char player;
    while (true)
    {
        valid = false;
        while (!valid)
        {
            if (turn % 2 != 0) player = 'X';
            else player = 'O';
            Game.printBoard();
            std::cout << "\n" << player << "'s turn:\n";
            std::cout << "Row:\n";
            std::cin >> row;
            row -= 1;
            std::cout << "Column:\n";
            std::cin >> col;
            col -= 1;
            valid = Game.isValidMove(row, col);
            if (valid)
            {
                Game.makeMove(row, col, player);
            }
        }
        win = Game.checkWin(player);
        if (win)
        {
            std::cout << player << "'s Win \nCongrats!";
            break;
        }
        tie = Game.checkTie();
        if (tie)
        {
            std::cout << "TIE!";
            break;
        }
        turn += 1;
    }
}
