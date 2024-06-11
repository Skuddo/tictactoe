#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <tuple>
#include <array>

class Board {
private:
    int size;
    std::vector<std::vector<char>> board;
    std::array<char, 2> players;
public:
    Board(int size = 3, const std::array<char, 2>& players = {'X', 'O'});
    void initBoard();
    void drawBoard();
    void setCell(int row, int col, char mark);
    void setCustomPlayer(int p);
    bool checkWin(char p);
    bool checkDraw();
    bool isCellEmpty(int row, int col);
    char getCell(int x, int y);
    int getSize();
};

#endif