#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <thread>
#include "board.hpp"
#include "gui.hpp"
#include "ai.hpp"

using namespace std::chrono_literals;

char currentPlayer;
std::array<char, 2> players = {'X', 'O'};

int main(){
    GUI gui;

    int customChars = gui.navigateMenu({"No","Yes"},2);
    if (customChars == 1){
        players[0] = ' ';
        players[1] = ' ';
        players[0] = gui.getCustomChar(0, players[0]);
        players[1] = gui.getCustomChar(1, players[1]);
    }

    int x = 0;
    int customSize = gui.navigateMenu({"No","Yes"},3);
    if (customSize == 1){
        gui.getCustomSize(x);
    }
    else {
        x=3;
    }

    int mode = gui.navigateMenu({"Singleplayer","Multiplayer"},0);
    
    Difficulty difficulty = HARD;
    AI* ai = nullptr;
    if (mode == 0){
        int diffSelection = gui.navigateMenu({"Easy mode","Hard mode"},1);
        difficulty = (diffSelection == 0) ? EASY : HARD;
        ai = new AI(players[0], players[1], difficulty);
    }

    Board board(x,players);
    
    gui.initGame(board, mode, difficulty);

    currentPlayer = players[0];
    int row = 0, col = 0;

    while(true) {
        mvprintw(2,2, "Player %c's turn", currentPlayer);
        wrefresh(stdscr);

        // AI move
        if ( mode == 0 && currentPlayer == players[1]){
            auto [aiRow, aiCol] = ai->findBestMove(board);
            board.setCell(aiRow, aiCol, currentPlayer);
        }
        else {
            gui.playerMove(board, row, col, currentPlayer);
            board.setCell(row, col, currentPlayer);
        }


        if (board.checkWin(currentPlayer)) {
            mvprintw(LINES / 4, (COLS - 20) / 2, "Player %c wins!", currentPlayer);
            wrefresh(stdscr);
            std::this_thread::sleep_for(5000ms);
            break;
        }

        if (board.checkDraw()) {
            mvprintw(LINES / 4, (COLS - 20) / 2, "It's a draw!");
            wrefresh(stdscr);
            std::this_thread::sleep_for(5000ms);
            break;
        }
        currentPlayer = (currentPlayer == players[0]) ? players[1] : players[0];
    }

    if (ai) {
        delete ai;
    }

    return 0;
}