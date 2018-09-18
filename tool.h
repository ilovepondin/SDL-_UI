#ifndef TOOL_H
#define TOOL_H
#include <string>

SDL_Surface* load_image(const char *file);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
void set_icon( int x, int y, SDL_Surface* icon_light, SDL_Surface *icon_dark, SDL_Surface* destination, bool icon_status );
SDL_Surface *load_text(const char* ttf_path, int ttf_size, const char* text_content,SDL_Color color);

const char* get_hour_char();
const char* get_min_char();
const char* get_speed(int speed_para);
char *int2str(char *s, int i);
//kevin 2018/01/25
void set_animation( int x, int y, SDL_Surface* ani_surface, SDL_Surface *backgnd, SDL_Surface* destination, bool ani_status, SDL_Rect clip);

#endif // TOOL_H

