#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <vector>
#include "board.hpp"

class GUI {
private:
    void rectangle(int y1, int x1, int y2, int x2);
public:
    GUI();
    ~GUI();
    void initGame(Board& board, int mode, int diff);
    void drawBoard(Board& board);
    void playerMove(Board& board, int &row, int &col, char player);
    int navigateMenu(const std::vector<std::string>& options, int menuType);
    char getCustomChar(int player, char& prevSymbol);
    void getCustomSize(int& size);
};

#endif