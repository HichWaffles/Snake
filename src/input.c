#include "input.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <stdio.h>

static DWORD old_mode;
static HANDLE h_stdin;

#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

static struct termios old_termios;
#endif

#define INPUT_BUFFER_SIZE 128
static int input_buffer[INPUT_BUFFER_SIZE];
static int head = 0;
static int tail = 0;

static int is_buffer_full(void) {
    return ((head + 1) % INPUT_BUFFER_SIZE) == tail;
}

static int is_buffer_empty(void) {
    return head == tail;
}

static void push_to_buffer(int key) {
    if (!is_buffer_full()) {
        input_buffer[head] = key;
        head = (head + 1) % INPUT_BUFFER_SIZE;
    }
}

void enable_raw_mode(void) {
#ifdef _WIN32
    h_stdin = GetStdHandle(STD_INPUT_HANDLE);
    if (h_stdin == INVALID_HANDLE_VALUE) return;
    GetConsoleMode(h_stdin, &old_mode);
    DWORD new_mode = old_mode;
    new_mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(h_stdin, new_mode);
#else
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
#endif
}

void disable_raw_mode(void) {
#ifdef _WIN32
    if (h_stdin) SetConsoleMode(h_stdin, old_mode);
#else
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
#endif
}

void poll_input(void) {
#ifdef _WIN32
    while (_kbhit()) {
        push_to_buffer(_getch());
    }
#else
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        push_to_buffer((unsigned char)c);
    }
#endif
}

int get_user_input(void) {
    if (is_buffer_empty()) {
        return -1;
    }
    int key = input_buffer[tail];
    tail = (tail + 1) % INPUT_BUFFER_SIZE;
    return key;
}

void hide_cursor(void) {
    printf("\033[?25l");
    fflush(stdout);
}

void show_cursor(void) {
    printf("\033[?25h");
    fflush(stdout);
}