#include "input.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <stdio.h>

static DWORD old_mode;
static HANDLE h_stdin;

void enable_raw_mode(void) {
  h_stdin = GetStdHandle(STD_INPUT_HANDLE);
  if (h_stdin == INVALID_HANDLE_VALUE)
    return;

  GetConsoleMode(h_stdin, &old_mode);

  DWORD new_mode = old_mode;
  new_mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
  SetConsoleMode(h_stdin, new_mode);
}

void disable_raw_mode(void) {
  if (h_stdin)
    SetConsoleMode(h_stdin, old_mode);
}

int get_user_input(void) {
  if (_kbhit()) {
    return _getch();
  }
  return -1;
}

#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

static struct termios old_termios;

void enable_raw_mode(void) {
  struct termios new_termios;

  tcgetattr(STDIN_FILENO, &old_termios);
  new_termios = old_termios;
  new_termios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void disable_raw_mode(void) {
  tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

int get_user_input(void) {
  char c;
  ssize_t n = read(STDIN_FILENO, &c, 1);
  return (n == 1) ? c : -1;
}
#endif

void hide_cursor(void) {
  printf("\033[?25l");
}

void show_cursor(void) {
  printf("\033[?25h");
}