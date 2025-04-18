//
// File: print.c
// print.c handles printing of pre-game strings
// @author Josh Bicking <josh1147582>
// // // // // // // // // // // // // // // // // // // // // // //

#define _BSD_SOURCE /* for unistd.h */
#ifdef _WIN32
#   include <Windows.h>
#   include <curses.h>
#   define SLEEP(delay) Sleep(delay/1000)
#else
#   include <curses.h>
#   include <unistd.h>
//#   define SLEEP(delay) sleep(delay/1000000)
void SLEEP(long delay) { while (delay -= 5) {} }
#endif

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "print.h"
#include "pass.h"

void slowPrint(char arr[], int line){
    int i;
    move(line, 0);
    for(i=0; (unsigned long)i<strlen(arr); i++){
        printw("%c",arr[i]);
        refresh();
        SLEEP(20000);
    }
}

void slowType(char arr[], int line){
    int i;
    flushinp();
    move(line, 1);
    for(i=0; (unsigned long)i<strlen(arr); i++){
        if (getch() == '\033') { pass(); } // on ESC, skip intro
        printw("%c",arr[i]);
        refresh();
    }
    while (getch() != '\n') {}
}

void passPrint(char arr[], int line){
    int i;
    move(line, 0);
    for(i=0; (unsigned long)i<strlen(arr); i++){
        printw("%c",arr[i]);
        refresh();
        SLEEP(20000);
    }
}

int kbhit(){
    /* Get the current char. */
    int ch = getch();

    /* Returns true if a key has been hit. False if it hasn't. */
    if (ch > ERR) {
        return 1;
    } else {
        return 0;
    }
}

void printChoices(int hex, char arr[], int line, int offset){
    int i;
    char hexstr[5];

    sprintf(hexstr, "%4x", hex);
    for(i=0; i<4; i++)
        if (isalpha(hexstr[i])) hexstr[i] = toupper(hexstr[i]);
    mvprintw(line,offset,"0x%s", hexstr);
    for(i=0; i<12; i++)
        mvprintw(line,7+offset+i,"%c",arr[i]);
    //move(line, 20+offset);
    refresh();
    SLEEP(30000);
}

// end
