#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "GameIO.h"
#include "GameState.h"
#include "enums.h"

class Game
{
    public:
        Game(const int CELL_HEIGHT, const int CELL_WIDTH);
        ~Game();

        void reset(Mark player, Mark cpu);
        Result start(Mark player, Mark cpu);
    private:
        GameIO* gIO;
        GameState* state;
        int currentCell;
        Mark player;
        Mark cpu;

        Result execGameloop();
        void moveCursor(Input index);
        void execMoveSeq(Result& r, bool& isRunning);
        void execPlayerMove(Result& r, bool& isRunning);
        void execCPUMove(Result& r, bool& isRunning);
        int getCPUMove();
        int minimax(bool isMaximizer, int alpha, int beta, int prevMove);
        int minimize(int alpha, int beta);
        int maximize(int alpha, int beta);
};
#endif // GAME_H_INCLUDED
