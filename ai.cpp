#include "ai.hpp"
#include <limits>

AI::AI(char aiChar, char pChar, Difficulty difficulty): difficulty(difficulty), aiChar(aiChar), pChar(pChar){
    maxDepth = (difficulty == EASY) ? 1 : std::numeric_limits<int>::max(); 
}

std::pair<int,int> AI::findBestMove(Board& board){
    int bestVal = std::numeric_limits<int>::min();
    std::pair<int,int> bestMove = {-1,-1};
    int boardSize  = board.getSize();
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if (board.isCellEmpty(i,j)){
                board.setCell(i,j,aiChar);
                int moveVal = minimax(board,0,false);
                board.setCell(i,j, ' ');

                if (moveVal > bestVal) {
                    bestMove = {i,j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int AI::minimax(Board& board, int depth, bool isMax){
int score = eval(board);

if (score == 10 || score == -10) return score - depth;
if (board.checkDraw()) return 0;
if (depth >= maxDepth) return 0;

int boardSize  = board.getSize();
if(isMax){
    int best = std::numeric_limits<int>::min();
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if(board.isCellEmpty(i,j)) {
                board.setCell(i,j,aiChar);
                best = std::max(best, minimax(board, depth + 1, !isMax));
                board.setCell(i,j,' ');
            }
        }
    }
    return best;
} else {
    int best = std::numeric_limits<int>::max();
    for (int i = 0; i < boardSize; i++){
        for (int j = 0; j < boardSize; j++){
            if(board.isCellEmpty(i,j)) {
                board.setCell(i,j,pChar);
                best = std::min(best, minimax(board, depth + 1, !isMax));
                board.setCell(i,j,' ');
            }
        }
    }
    return best;
}
}

int AI::eval(Board& board){
    if (board.checkWin(aiChar)) return 10;
    else if (board.checkWin(pChar)) return -10;

    int score = 0;

    for (int i = 0; i < board.getSize(); i++){
        score += evaluateLine(board, 0, i, 1, 0);
        score += evaluateLine(board, i, 0, 0, 1);
    }

    score += evaluateLine(board, 0, 0, 1, 1);
    score += evaluateLine(board, 0, board.getSize() - 1, 1, -1);

    return score;
}

int AI::evaluateLine(Board& board, int startRow, int startCol, int stepRow, int stepCol) {
    int aiCount = 0;
    int pCount = 0;
    int size = board.getSize();
    for (int i=0; i < board.getSize(); i++){
        char cell = board.getCell(startRow + i * stepRow, startCol + i * stepCol);
        if (cell == aiChar) aiCount++;
        if (cell == pChar) pCount++;
    }

    if (aiCount > 0 && pCount == 0) return aiCount == size ? 5 : 1;
    if (pCount > 0 && aiCount == 0) return pCount == size ? -5 : -1;
    
    return 0;
}