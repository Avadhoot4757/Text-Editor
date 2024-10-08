#include <ncurses.h>
#include <iostream>
#include <vector>
#include "../pieces/piecetable.h"
using namespace std;

struct CharPosition {
    int x;
    int y;
    char character;
};

void display(PieceTable& pt){
    initscr();
    cbreak();
    noecho();
    clear();
    vector<Piece>pieces=pt.getPieces();
    int sy=0;
    for(size_t i=0;i<pieces.size();i++){
           int sx=pieces[i].start_index;
           int ex=pieces[i].size;
           int buff=pieces[i].buffer;
           for(int j=0;j<ex;j++){
                mvprintw(sy,sx+i,"%c",(*pt.getBuffer(buff))[sx+1]);
           }
           sy++;
    }
    refresh();            
    getch();              
    endwin();            
}

char getAll(int& currx, int& curry) {
    getyx(stdscr, curry, currx);
    return mvinch(curry, currx) & A_CHARTEXT;
}

int main() {
    Initialize ncurses
    initscr();
    cbreak();               
    keypad(stdscr, TRUE);  
    noecho();               
    scrollok(stdscr, TRUE); 

    vector<CharPosition> ;

    int ch;
    int y = 0, x = 0;
    bool shouldEndWin = false;

    while (!shouldEndWin){
        ch = getch();
        switch (ch) {
            case KEY_BACKSPACE:
                getyx(stdscr, y, x);
                if (x > 0) {
                    mvwdelch(stdscr, y, x - 1);
                    if (x > 0) move(y, x - 1); 
                }
                break;
            case KEY_UP:
                getyx(stdscr, y, x);
                if (y > 0) { 
                    move(y - 1, x);
                }
                break;
            case KEY_DOWN:
                getyx(stdscr, y, x);
                if (y < LINES - 1) {
                    move(y + 1, x);
                }
                break;
            case KEY_LEFT:
                getyx(stdscr, y, x);
                if (x > 0) {
                    move(y, x - 1);
                }
                break;
            case KEY_RIGHT:
                getyx(stdscr, y, x);
                if (x < COLS - 1) {
                    move(y, x + 1);
                } else {
                    if (y < LINES - 1) {
                        move(y + 1, 0);  
                    }
                }
                break;
            case KEY_F(7):  
                shouldEndWin = true;
                break;
            default:
                mvprintw(y, x, "%c", ch);
                charPositions.push_back({x, y, (char)ch});
                getyx(stdscr, y, x);
                break;
        }
        refresh();
    }

    endwin();  
    for (const auto& pos : charPositions) {
        cout << "Character: " << pos.character << " | Position: (" << pos.x << ", " << pos.y << ")" << endl;
    }
    string original_buffer="THIS_";
    string add_buffer="is_the_new_world";

    PieceTable pt(&original_buffer,&add_buffer);
    display(pt);

    return 0;
}





