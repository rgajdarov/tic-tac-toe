#include "GameIO.h"


GameIO::GameIO(const int CELL_HEIGHT, const int CELL_WIDTH) :
                    CELL_HEIGHT{CELL_HEIGHT}, CELL_WIDTH{CELL_WIDTH}
{
    for(int i = 0; i < 9; i++)
    {
        int y = i / 3;
        int x = i % 3;
        grid[i] = newwin(CELL_HEIGHT, CELL_WIDTH, y * CELL_HEIGHT, x * CELL_WIDTH);
        keypad(grid[i], TRUE);
    }
}

GameIO::~GameIO()
{
    for(WINDOW* cell : grid)
    {
        delwin(cell);
        cell = nullptr;
    }
}


void GameIO::moveCursor(int index)
{
    wmove(grid[index], CELL_HEIGHT / 2, CELL_WIDTH / 2);
    wrefresh(grid[index]);
}

void GameIO::markCell(int index, Mark m)
{
    mvwaddch(grid[index], CELL_HEIGHT / 2, CELL_WIDTH / 2, m);
    wrefresh(grid[index]);
}

void GameIO::reset()
{
    for(WINDOW* cell : grid)
    {
        werase(cell);
        box(cell, 0, 0);
        wrefresh(cell);
    }
}

Input GameIO::getInput(int index) const
{
    Input i = Input::NONE;
    int userInput = wgetch(grid[index]);
    switch(userInput)
    {
        case KEY_BACKSPACE:
            i = Input::ABORT;
            break;
        case KEY_UP:
            i = Input::UP;
            break;
        case KEY_DOWN:
            i = Input::DOWN;
            break;
        case KEY_LEFT:
            i = Input::LEFT;
            break;
        case KEY_RIGHT:
            i = Input::RIGTH;
            break;
        case '\n':
            i = Input::MARK;
            break;
    }
    return i;
}
