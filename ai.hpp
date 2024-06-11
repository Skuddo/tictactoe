#ifndef AI_HPP
#define AI_HPP

#include "board.hpp"

enum Difficulty {
    EASY,
    HARD
};

class AI {
public:
    AI(char aiChar, char pChar, Difficulty difficulty);
    std::pair<int,int> findBestMove(Board& board);

private:
    int minimax(Board& board, int depth, bool isMax);
    int eval(Board& board);
    int evaluateLine(Board& board, int startRow, int startCol, int stepRow, int stepCol);
    int maxDepth;
    char aiChar;
    char pChar;
    Difficulty difficulty;
};

#endif 