#include "GameState.h"

GameState::GameState()
{
    reset();
}

void GameState::reset()
{
    for(Mark& cell : grid)
    {
        cell = Mark::E;
    }
}

bool GameState::hasUnmarked() const
{
    return  getEmptyCellCount() != 0;
}

int GameState::getEmptyCellCount() const
{
    int counter = 0;
    for(const Mark& m : grid)
    {
        if(m == Mark::E) counter++;
    }
    return counter;
}

void GameState::markCell(int index, Mark m)
{
    if(index < 0 || index > 8) return;
    grid[index] = m;
}

bool GameState::isWinning(int index) const
{
    bool winning = false;
    if(index % 4 == 0) winning |= checkMainDiag();
    if(index == 2 || index == 4 || index == 6) winning |= checkSndDiag();
    winning |= checkRow(index / 3);
    winning |= checkCol(index % 3);
    return winning;
}

bool GameState::isMarked(int index) const
{
    return grid[index] != Mark::E;
}

bool GameState::checkMainDiag() const
{
    return grid[0] == grid[4] && grid[0] == grid[8];
}

bool GameState::checkSndDiag() const
{
    return grid[2] == grid[4] && grid[2] == grid[6];
}

bool GameState::checkRow(int row) const
{
    int first = row * 3;
    return grid[first] == grid[first + 1] && grid[first] == grid[first + 2];
}

bool GameState::checkCol(int col) const
{
    return grid[col] == grid[col + 3] && grid[col] == grid[col + 6];
}
