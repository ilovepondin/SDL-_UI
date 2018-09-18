#include "gui.h"

// -----------------------------------------------------------------------------
// gui_text
// -----------------------------------------------------------------------------
gui_text::gui_text(SDL_Surface *screen, SDL_Surface *background,
               int x, int y, int w, int h, align_t align,
               const char *font, SDL_Color color, short pixel)
{
    this->screen = screen;
    this->background = background;
    this->area.x = x;
    this->area.y = y;
    this->area.w = w;
    this->area.h = h;
    this->align = align;
    this->color = color;
    this->pixel = pixel;
    this->text = "";

    mask = area;
    mask.h = pixel;

    ttf = TTF_OpenFont(font, pixel);
}

gui_text::~gui_text()
{
    SDL_FreeSurface(txt);
}

void gui_text::update(string text)
{
    if(this->text != text)
    {
        this->text = text;

        // clean old text area
        SDL_BlitSurface(background, &mask, screen, &mask);

        // before draw new text, drop old first
        SDL_FreeSurface(txt);

        txt = TTF_RenderText_Blended(ttf, text.data(), color);

        SDL_BlitSurface(txt, NULL, screen, masker());
    }
}

SDL_Rect* gui_text::masker()
{
    if (align == align_right)
    {
        mask.x = area.x+area.w-txt->w;
    }
    else if (align == align_center)
    {
//        mask.x = (area.x+area.w-txt->w)/2;
        mask.x = area.x+(area.w/2)-(txt->w)/2;
    }

    //printf("t.w:%d, a.x:%d, a.w:%d, m.x:%d\n", txt->w, area.x, area.w, mask.x);

    return &mask;
}

// -----------------------------------------------------------------------------
// gui_number
// -----------------------------------------------------------------------------
gui_number::gui_number(SDL_Surface *screen, SDL_Surface *background,
                   int x, int y, int w, int h, align_t align,
                   const char *font, SDL_Color color, short pixel)
    : gui_text(screen, background, x, y, w, h, align,
             font, color, pixel)
{
}

gui_number::~gui_number()
{
}

void gui_number::update(long number)
{
    if (this->number != number)
    {
        this->number = number;
        gui_text::update(std::to_string(number));
    }
}

// -----------------------------------------------------------------------------
// gui_image
// -----------------------------------------------------------------------------
gui_image::gui_image(SDL_Surface *screen, SDL_Surface *background,
                       int x, int y, const char *file)
{
    this->screen = screen;
    this->background = background;

    mask.x = x;
    mask.y = y;

    image = IMG_Load(file);

#if 0 //strange, this cause edge not smooth
    SDL_Surface* optimized;

    if( image != NULL )
    {
        optimized = SDL_DisplayFormat(image);
        SDL_SetColorKey(optimized, SDL_SRCCOLORKEY, SDL_MapRGB(optimized->format, 0, 0, 0));
        SDL_FreeSurface(image);
    }

    image = optimized;
#endif

    // set mask size by loaded image
    mask.w = image->w;
    mask.h = image->h;
}

gui_image::~gui_image()
{
    SDL_FreeSurface(image);
}

void gui_image::update(bool on)
{
    static bool first = true;

    if ((this->on != on) || (first))
    {

        this->on = on;

        if (on)
        {
            SDL_BlitSurface(image, NULL, screen, &mask);
        }
        else
        {
            SDL_BlitSurface(background, &mask, screen, &mask);
        }
        first = false;

    }

}




