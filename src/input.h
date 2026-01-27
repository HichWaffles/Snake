#ifndef INPUT_H
#define INPUT_H

void enable_raw_mode(void);
void disable_raw_mode(void);
void poll_input(void);
int get_user_input(void);
void hide_cursor(void);
void show_cursor(void);

#endif
