#ifndef GUI_H
#define GUI_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <string>

using namespace std;

class gui_text
{
public:
    typedef enum  {
        align_left,
        align_right,
        align_center
    } align_t;

    gui_text(SDL_Surface *screen, SDL_Surface *background,
             int x, int y, int w, int h, align_t align,
             const char *font, SDL_Color color, short pixel);

    ~gui_text();

    void update(string text);
    void render(string text);

private:
    char *int2str(char *s, int i);
    SDL_Rect *masker();

private:
    SDL_Surface *screen;
    SDL_Surface *background;
    align_t align;
    SDL_Color color;
    short pixel;

    TTF_Font *ttf;
    SDL_Surface *txt;
    SDL_Rect mask;
    SDL_Rect area;

    string text;
};


class gui_number : gui_text
{
public:
    gui_number(SDL_Surface *screen, SDL_Surface *background,
             int x, int y, int w, int h, align_t align,
             const char *font, SDL_Color color, short pixel);

    ~gui_number();

    void update(long number);

private:
    long number;
};


class gui_image
{
public:
    gui_image(SDL_Surface *screen, SDL_Surface *background,
             int x, int y, const char *file);

    ~gui_image();

    void update(bool on);

private:
    SDL_Surface *screen;
    SDL_Surface *background;

    SDL_Surface *image;
    SDL_Rect mask;

    bool on;
};

#endif // GUI_H
