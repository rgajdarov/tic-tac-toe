#include "Game.h"

constexpr int MIN = -10;
constexpr int MAX = 10;
constexpr int DRAWS = 0;

constexpr int CENTRAL_CELL = 4;

Game::Game(const int CELL_HEIGHT, const int CELL_WIDTH)
{
    gIO = new GameIO(CELL_HEIGHT, CELL_WIDTH);
    state = new GameState();
    currentCell = CENTRAL_CELL;
    player = Mark::E;
    cpu = Mark::E;
}

Game::~Game()
{
    delete gIO;
    gIO = nullptr;
    delete state;
    state = nullptr;
}

void Game::reset(Mark player, Mark cpu)
{
    gIO->reset();
    state->reset();
    currentCell = CENTRAL_CELL;
    this->player = player;
    this->cpu = cpu;
    gIO->moveCursor(currentCell);
}

Result Game::start(Mark player, Mark cpu)
{
    reset(player, cpu);
    Result r = execGameloop();
    return r;
}

Result Game::execGameloop()
{
    Input i;
    bool isRunning = true;
    Result r = ABORTED;
    if(player == Mark::O) execCPUMove(r, isRunning);
    while(isRunning)
    {
        i = gIO->getInput(currentCell);
        switch(i)
        {
            case ABORT:
                isRunning = false;
                break;
            case NONE:
            case UP:
            case DOWN:
            case LEFT:
            case RIGTH:
                moveCursor(i);
                break;
            case MARK:
                execMoveSeq(r, isRunning);
                break;
        }
    }
    return r;
}

void Game::moveCursor(Input dir)
{
    currentCell += dir;
    if(currentCell > -1 && currentCell < 9)
        gIO->moveCursor(currentCell);
    else
        currentCell -= dir;
}

void Game::execMoveSeq(Result& r, bool& isRunning)
{
    if(state->isMarked(currentCell)) return;
    execPlayerMove(r, isRunning);
    if(!isRunning) return;
    execCPUMove(r, isRunning);
    gIO->moveCursor(CENTRAL_CELL);
    currentCell = CENTRAL_CELL;
}

void Game::execPlayerMove(Result& r, bool& isRunning)
{
    gIO->markCell(currentCell, player);
    state->markCell(currentCell, player);
    if(state->isWinning(currentCell))
    {
        r = PLAYER;
        isRunning = false;
    }

    if(!state->hasUnmarked())
    {
        r = DRAW;
        isRunning = false;
    }
}

void Game::execCPUMove(Result& r, bool& isRunning)
{
    int index = getCPUMove();
    state->markCell(index, cpu);
    gIO->markCell(index, cpu);
    if(state->isWinning(index))
    {
        r = CPU;
        isRunning = false;
    }

    if(!state->hasUnmarked())
    {
        r = DRAW;
        isRunning = false;
    }
}

int Game::getCPUMove()
{
    int cpuMove = 0;
    int alpha = -100;
    int beta = 100;
    for(int i = 0; i < 9; i++)
    {
        if(!state->isMarked(i))
        {
            state->markCell(i, cpu);
            int result = minimax(false, alpha, beta, i);
            state->markCell(i, Mark::E);
            if(result > alpha)
            {
                alpha = result;
                cpuMove = i;
            }
        }
    }
    return cpuMove;
}

int Game::minimax(bool isMaximizer, int alpha, int beta, int prevMove)
{
    if(state->isWinning(prevMove)) return isMaximizer ? MIN : MAX;
    if(!state->hasUnmarked()) return DRAWS;
    int bestValue;
    if(isMaximizer)
        bestValue = maximize(alpha, beta);
    else
        bestValue = minimize(alpha, beta);
    return bestValue;
}

int Game::minimize(int alpha, int beta)
{
    for(int i = 0; i < 9; i++)
    {
        if(!state->isMarked(i))
        {
            state->markCell(i, player);
            int result = minimax(true, alpha, beta, i);
            state->markCell(i, Mark::E);
            beta = result < beta ? result : beta;
            if(alpha >= beta)
                break;
        }
    }
    return beta;
}

int Game::maximize(int alpha, int beta)
{
    for(int i = 0; i < 9; i++)
    {
        if(!state->isMarked(i))
        {
            state->markCell(i, cpu);
            int result = minimax(false, alpha, beta, i);
            state->markCell(i, Mark::E);
            alpha = result > alpha ? result : alpha;
            if(alpha >= beta)
                break;
        }
    }
    return alpha;
}
