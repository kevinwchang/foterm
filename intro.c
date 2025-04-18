//
// File: intro.c
// intro.c plays the introduction sequence
// @author Josh Bicking <josh1147582>
// // // // // // // // // // // // // // // // // // // // // // //

#define _BSD_SOURCE /* for unistd.h */
#ifdef _WIN32
// Windows implements sleep in Windows.h with Sleep(milliseconds)
#   include <curses.h>
#   include <Windows.h>
#   define SLEEP(delay) Sleep(delay/1000)
#else
// Unix requires unistd.h for usleep(microseconds).
// usleep/1000 = Sleep
#   include <curses.h>
#   include <unistd.h>
//#   define SLEEP(delay) sleep(delay/200000)
void SLEEP(long delay) { while (delay -= 5) {} }
#endif

#include <string.h>

#include "print.h"
#include "intro.h"

/// Plays the introduction sequence.
///
void intro(){
    clear();
    slowPrint("SECURITY RESET...", 0);
    SLEEP(250000);

    slowPrint("WELCOME TO ROBCO INDUSTRIES (TM) TERMLINK", 2);
    mvprintw(0, 0, "                 "); // clear SECURITY RESET...
    mvprintw(4, 0, ">");
    move(4, 1);
    refresh();

    slowType("SET TERMINAL/INQUIRE", 4);

    slowPrint("RIT-V300", 6);

    mvprintw(8, 0, ">");
    refresh();
    slowType("SET FILE/PROTECTION=OWNER:RWED ACCOUNTS.F", 8);

    mvprintw(9, 0, ">");
    refresh();
    slowType("SET HALT RESTART/MAINT", 9);

    slowPrint("Initializing Robco Industries(TM) Boot Agent v2.3.0", 11);
    slowPrint("RETROS BIOS", 12);
    slowPrint("RBIOS-4.02.08.00 52EE5.E7.E8", 13);
    slowPrint("Copyright 2201-2203 Robco Ind.", 14);
    slowPrint("Uppermem: 64 KB", 15);
    slowPrint("Root (5A8)", 16);
    slowPrint("Maintenance Mode", 17);

    mvprintw(19, 0, "%c", '>');
    refresh();
    slowType("RUN DEBUG/ACCOUNTS.F", 19);

    SLEEP(50000);
}

