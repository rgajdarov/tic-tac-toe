#include "UI.h"

UI::UI(const int CELL_HEIGHT, const int CELL_WIDTH)
{
    ui = newwin(3, 50, 3 * CELL_HEIGHT + 1, 0);
}

UI::~UI()
{
    delwin(ui);
    ui = nullptr;
}

void UI::setMarks(Mark& player, Mark& cpu)
{
    werase(ui);
    waddstr(ui, "Xs or Os - (x / o) ");
    wrefresh(ui);
    int input = -1;
    player = Mark::X;
    cpu = Mark::O;
    while(input != 'x' && input != 'o')
        input = wgetch(ui);
    if(input == 'o')
    {
        player = Mark::O;
        cpu = Mark::X;
    }
}

void UI::displayHelp()
{
    werase(ui);
    waddstr(ui, "Mark cell - ENTER\n");
    waddstr(ui, "Navigate - ARROWS\n");
    waddstr(ui, "Stop game - BACKSPACE");
    wrefresh(ui);
}

std::string UI::convertToText(Result r) const
{
    std::string message;
    switch(r)
    {
        case DRAW:
            message = "The game was a DRAW.";
            break;
        case PLAYER:
            message = "Player won.";
            break;
        case CPU:
            message = "CPU won.";
            break;
        case ABORTED:
            message = "The game was ABORTED.";
            break;
    }
    return message;
}

bool UI::restartGame(Result r)
{
    werase(ui);
    std::string message = convertToText(r);
    wprintw(ui, "%s Another game? - (y / n) ", message.c_str());
    int input = -1;
    while(input != 'y' && input != 'n')
        input = wgetch(ui);
    if(input == 'y') return true;
    return false;
}
