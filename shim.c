#include <curses.h>
#include <fcntl.h>
#include <unistd.h>

innstr(char *str, int n)
{
  int x, y;
  getyx(stdscr, y, x);
  while (n-- && (*str = mvinch(y, x++)) != ERR) { str++; }
  if (*str == ERR) { return ERR; }
  return OK;
}

void nodelay(void *win, bool bf)
{
  static int oldflags;
  static bool enabled = 0;

  if (bf && !enabled)
  {
    oldflags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldflags | O_NONBLOCK);
    enabled = 1;
  }
  else if (enabled)
  {
    fcntl(STDIN_FILENO, F_SETFL, oldflags);
    enabled = 0;
  }
}

void flushinp()
{
  int ch;
  nodelay(stdscr, 1);
  ch = getch();
  while(ch > ERR)
    ch = getch();
  nodelay(stdscr, 0); // FIXME leave in nodelay mode if it was already?
}
