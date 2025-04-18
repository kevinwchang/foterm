#ifdef _WIN32
// Windows builds require curses.h for the PDcurses library.
#   include <curses.h>
#else
// Unix builds require ncurses.h for the Ncurses library.
#   include <curses.h>
#endif

#include <stdlib.h>
#include <time.h> /* For making a random seed */
#include <string.h> /* For strcmp, to identify argv[1] */
#include <signal.h>
#include "intro.h" /* To launch intro */
#include "pass.h" /* To launch pass */
#include "wordParse.h" /* To read the file */

void INThandler(int sig)
{
  fputs(CL, stdout); // don't use clear() just in case we're not in curses
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]){

    if(argc > 1 && !strcmp(argv[1], "--help")){
        printf("Usage: %s [--DIFFICULTY]\n\n", argv[0]);
        exit(0);
    }

    // Check if a difficulty arg was given
    if(argc > 1){
        if(!strcmp(argv[1], "--very-easy")) {
            setVeryEasy();
        }
        if(!strcmp(argv[1], "--easy")) {
           setEasy();
        }
        else if(!strcmp(argv[1], "--average")) {
           setAverage();
        }
        else if(!strcmp(argv[1], "--hard")) {
           setHard();
        }
        else if(!strcmp(argv[1], "--very-hard")) {
           setVeryHard();
        }
        else {
            printf("Invalid command. Type \"%s --help\" for usage and a list of commands.\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    // Otherwise, read the file for words
    else {
        //readWordsFromFile();
        setVeryEasy();
    }

    // Read what should be launch on completion/victory
    readLaunches();

    // Read the key config
    readKeys();

    // Gen a random seed
    srand ( (unsigned)time(NULL) );

    // Begin curses
    initscr();
    delwin(stdscr);
    stdscr = newwin(23, 54, 1, 13);
    cbreak();
    noecho();
    refresh();
    //attron(A_BOLD);
    //keypad(stdscr, TRUE);
    // Check for color support. Start color if it exists.
    /*if(has_colors() == 1){
        start_color();
        //init_pair(1,COLOR_GREEN,COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }*/

    signal(SIGINT, INThandler);

    // Run intro
    intro();

    // Run pass
    pass();

    return EXIT_SUCCESS;
}

