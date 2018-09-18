#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include<SDL/SDL.h>

void home_loop();
bool home_init(SDL_Surface *surface);
bool home_deinit();
void home_handle_input(uint8_t type, SDLKey key);
void home_handle_ipc(char *from, char *d, size_t l);


//void turn_right_blink(void*);
//void turn_left_blink(void*);


#endif // FIRSTPAGE_H
