#ifndef GAMEIO_H_INCLUDED
#define GAMEIO_H_INCLUDED

#include <ncurses.h>
#include "enums.h"

class GameIO
{
    public:
        GameIO(const int CELL_HEIGHT, const int CELL_WIDTH);
        ~GameIO();

        Input getInput(int index) const;
        void reset();
        void moveCursor(int index);
        void markCell(int index, Mark m);

    private:
        const int CELL_HEIGHT;
        const int CELL_WIDTH;
        WINDOW* grid[9];
};

#endif // GAMEIO_H_INCLUDED
