#include "board.hpp"
#include <ncurses.h>
#include <algorithm>
#include <string>

Board::Board(int size, const std::array<char, 2>& players) : size(size), players(players) {
    initBoard();
}

void Board::initBoard() {
    board.resize(size, std::vector<char>(size, ' '));
}

void Board::drawBoard() {
    clear();

    int startX = (COLS - ((size - 1) * 4) - 1) / 2;
    int startY = (LINES / 2) - (size *2)/2;

    for (int i = 0; i < board[0].size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            mvaddch(startY + (2 * i), startX + (4 * j), board[i][j]);
            if (j < size - 1) {
                mvaddch(startY + (2 * i), startX + (4 * j) + 2, '|');
            }
        }
        if (i < size - 1) {
            mvprintw(startY + (2 * i) + 1, startX-1, "---");
            for (int k = 1; k < size; k++) {
                mvprintw(startY + (2 * i) + 1, startX + 4 * k - 2, "+---");
            }
        }
    }
    wrefresh(stdscr);
}

    bool Board::checkWin(char p){
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 2; j++) {
                if (board[i][j] == p && board[i][j + 1] == p && board[i][j + 2] == p)
                { return true;} 
            }
        }

        for (int i = 0; i < size - 2; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == p && board[i + 1][j] == p && board[i + 2][j] == p)
                { return true;} 
            }
        }
    
        for (int i = 0; i < size - 2; i++) {
            for (int j = 0; j < size - 2; j++) {
                if (board[i][j] == p && board[i + 1][j + 1] == p && board[i + 2][j + 2] == p)
                { return true;} 
            }
        }

        for (int i = 0; i < size - 2; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == p && board[i + 1][j - 1] == p && board[i + 2][j - 2] == p)
                { return true;} 
            }
        }
        return false;
    }

    bool Board::checkDraw(){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
            if (isCellEmpty(i,j)) return false;
        }
    }
    return true;
    }

    void Board::setCell(int x, int y, char p){
        board[x][y] = p;
    }

    bool Board::isCellEmpty(int x, int y) {
        return board[x][y] == ' ';
    }

    char Board::getCell(int x, int y) {
        return board[x][y];
    }

    int Board::getSize(){
        return size;
    }