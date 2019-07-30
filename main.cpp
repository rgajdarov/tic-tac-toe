#include <ncurses.h>
#include "UI.h"
#include "Game.h"
#include "enums.h"

constexpr int CELL_HEIGHT = 5;
constexpr int CELL_WIDTH = 9;

int main()
{
    initscr();
    noecho();
    cbreak();

    Game g(CELL_HEIGHT, CELL_WIDTH);
    UI ui(CELL_HEIGHT, CELL_WIDTH);

    while(true)
    {
        Mark player, cpu;
        ui.setMarks(player, cpu);
        g.reset(player, cpu);
        ui.displayHelp();
        Result r = g.start(player, cpu);
        if(!ui.restartGame(r)) break;
    }

    endwin();
    return 0;
}

