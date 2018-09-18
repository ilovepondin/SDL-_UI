#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include "tool.h"

//kevin 2018/01/08
#include "time.h"
#include "stdio.h"
#include "stdlib.h"




//kevin 2018/01/09


const char* get_speed(int speed_para)
{
    static char speed_array[3];
    sprintf(speed_array, "%d", speed_para);
    return speed_array;
}




const char* get_hour_char()
{

    static char hour[3];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(hour, "%d", tm.tm_hour);
    std::string len = hour;
    if(len.length() == 1)
    {
        hour[1] = hour[0];
        hour[0] = '0';
    }
    return hour;
}

const char* get_min_char()
{
    static char min[3];


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(min, "%d", tm.tm_min);
    std::string len = min;
    if(len.length() == 1)
    {
        min[1] = min[0];
        min[0] = '0';
    }
    return min;



}

char *int2str(char *s, int i)
{
    sprintf(s,"%d",i);
    return s;
}


SDL_Surface* load_image(const char *file)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(file);
    return loadedImage;
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0 ) );
        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}





void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset);
}


void set_animation( int x, int y, SDL_Surface* ani_surface, SDL_Surface *backgnd, SDL_Surface* destination, bool ani_status, SDL_Rect clip)
{


    if(ani_status == 1)
    {

        //        SDL_FillRect(destination, &clip, SDL_MapRGB(destination->format, 0, 0, 0) );

        apply_surface(x, y, backgnd, destination, &clip);

        apply_surface(x, y , ani_surface, destination, NULL);}

    else
    {
        //        SDL_FillRect(destination, &clip, SDL_MapRGB(destination->format, 0, 0, 0) );
        apply_surface(x, y, backgnd, destination, &clip);
    }

}


//if status == true : using light pic, else using dark pic
void set_icon( int x, int y, SDL_Surface* icon_light, SDL_Surface *icon_dark, SDL_Surface* destination, bool icon_status )
{

    SDL_Rect clip;
    clip.x = x;
    clip.y = y;
    clip.w = icon_light->w;
    clip.h = icon_light->h;

    if(icon_status == 1)
    {

        //        SDL_FillRect(destination, &clip, SDL_MapRGB(destination->format, 0, 0, 0) );

        apply_surface(x, y, icon_dark, destination, &clip);

        apply_surface(x, y , icon_light , destination, NULL);}

    else
    {
        //        SDL_FillRect(destination, &clip, SDL_MapRGB(destination->format, 0, 0, 0) );
        apply_surface(x, y, icon_dark, destination, &clip);
    }




}


SDL_Surface* load_text(const char* ttf_path, int ttf_size, const char* text_content,SDL_Color color)
{

    TTF_Font *ttf = TTF_OpenFont(ttf_path, ttf_size);
    SDL_Surface *surface = TTF_RenderUTF8_Blended(ttf,text_content, color );
    if(surface == NULL ||ttf == NULL )
    {
        printf("load_text error\n");
        exit(0);
    }
    return surface;
}
