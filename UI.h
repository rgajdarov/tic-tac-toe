#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <ncurses.h>
#include <string>
#include "enums.h"

class UI
{
    public:
        UI(const int CELL_HEIGHT, const int CELL_WIDTH);
        ~UI();

        void setMarks(Mark& player, Mark& cpu);
        void displayHelp();
        bool restartGame(Result r);
    private:
        WINDOW* ui;
        std::string convertToText(Result r) const;
};

#endif // UI_H_INCLUDED
