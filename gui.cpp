#include "gui.hpp"
#include <ncurses.h>
#include <chrono>
#include <iostream>
#include <tuple>

GUI::GUI() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
}

GUI::~GUI() {
    nocbreak();
    echo();
    curs_set(1);
    endwin(); 
} 

void GUI::rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void GUI::initGame(Board& board,int mode, int diff){
    clear();
    rectangle(0,0,LINES-1,COLS-1);
    wrefresh(stdscr);

    std::string gamemode = (mode == 0) ? "Singleplayer" : "Multiplayer";
    
    board.initBoard();
    drawBoard(board);
    mvprintw(2, 4, "Tic-Tac-Toe");
    mvprintw(4, 4, "%s", gamemode.c_str());
    if (mode == 1){
        std::string difficulty = (diff == 1) ? "Easy mode" : "Hard mode";
        mvprintw(5, 4, "%s", difficulty.c_str());
    }
    wrefresh(stdscr);
}

void GUI::drawBoard(Board& board) {
    clear();
    int size = board.getSize();
    int startX = (COLS - ((size - 1) * 4) - 1) / 2;
    int startY = (LINES / 2) - (size *2)/2;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mvaddch(startY + (2 * i), startX + (4 * j), board.getCell(i,j));
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

int GUI::navigateMenu(const std::vector<std::string>& options, int menuType){
    int highlight = 0;
    int c;

    clear();
    rectangle(0,0,LINES-1,COLS-1);

    std::string message;
    if (menuType == 0){
        message = "Select mode: ";
    }
    else if (menuType == 1){
        message = "Select difficulty: ";
    }
    else if (menuType == 2){
        message = "Custom players? ";
    }
    else if (menuType == 3){
        message = "Custom size? ";
    }

    mvprintw(LINES/2,(COLS/2) - 26, "%s", message.c_str());
    wrefresh(stdscr);

    while(1){
        for (int i = 0; i < options.size(); i++){
            if(i == highlight){
                wattron(stdscr, A_REVERSE);
            }
            mvprintw(LINES/2 + i, (COLS - options[i].length()) /2, "%s", options[i].c_str());
            wattroff(stdscr, A_REVERSE);
        }
        c = getch();
        switch(c) {
            case KEY_UP:
                highlight = (highlight == 0) ? options.size() - 1: highlight -1;
                break;
            case KEY_DOWN:
                highlight = (highlight == options.size() -1) ?  0 : highlight +1;
                break;
            case 10:
                return highlight;
            default:
                break;
        }
    }
}

void GUI::playerMove(Board& board, int &row, int &col, char player){
    int c;
    int size = board.getSize() - 1;
    while(true){
        c = getch();
        switch(c) {
                case KEY_UP:
                row = (row == 0) ? size : row - 1;
                break;
            case KEY_DOWN:
                row = (row == size) ? 0 : row + 1;
                break;
            case KEY_LEFT:
                col = (col == 0) ? size : col - 1;
                break;
            case KEY_RIGHT:
                col = (col == size) ? 0 : col + 1;
                break;
            case 10:
                if (board.isCellEmpty(row ,col)){
                    return;
                }
                break;
            default:
                break;
        }
        drawBoard(board);
        int startX = (COLS - (size * 4) - 1) / 2;
        int startY = (LINES / 2) - (size *2) /2 ;
        mvaddch(startY + (2 * row) - 1, startX + (4 * col), player | A_REVERSE);
        wrefresh(stdscr);
    }
}

char GUI::getCustomChar(int player, char& prevSymbol){
    clear();
    rectangle(0, 0, LINES-1, COLS-1);
    mvprintw(LINES/2,(COLS/2)-20, "Player %d, enter your character: ", player);
    wrefresh(stdscr);
    char c = getch();
    while (c == prevSymbol){
        c = getch();
    }
    return c;
}

void GUI::getCustomSize(int& size){
    clear();
    rectangle(0, 0, LINES-1, COLS-1);
    mvprintw(LINES/2,(COLS/2)-20, "Enter size: ");
    wrefresh(stdscr);
    char x = getch();
    while (((int)x - 48) <= 3, ((int)x - 48) >= 10){
        x = getch();
    }
    size = (int)x - 48;
}