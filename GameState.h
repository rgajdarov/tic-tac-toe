#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "enums.h"

class GameState
{
    public:
        GameState();
        void reset();
        bool hasUnmarked() const;
        int getEmptyCellCount() const;
        void markCell(int index, Mark m);
        bool isWinning(int index) const;
        bool isMarked(int index) const;
    private:
        Mark grid[9];

        bool checkMainDiag() const;
        bool checkSndDiag() const;
        bool checkRow(int row) const;
        bool checkCol(int col) const;
};

#endif // GAMESTATE_H_INCLUDED
