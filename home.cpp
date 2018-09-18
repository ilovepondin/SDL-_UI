
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>


//kevin 2018/01/10
//#include <pthread.h>
#include <unistd.h>
#include "home.h"
#include "tool.h"
#include "manager.h"
#include "gui.h"
//kevin 2018/01/23
#include "vehicle.h"

using namespace std;

/*------------------------------------------------------------------------------
 * Define
 *----------------------------------------------------------------------------*/
#define YEAR_SET 1900
#define MON_SET 1

typedef enum {
    CMODE_INIT      = 0x00,
    CMODE_LOOP      = 0x01,
    CMODE_DEINIT    = 0x02
} CMODE_t;

#define FONT_KHAND_SEMIBOLD "ttf/Khand/Khand-SemiBold.ttf"
#define FONT_DEJAVUSANSMONO "ttf/DejaVuSansMono.ttf"
#define FONT_KHAND_REGULAR  "ttf/Khand/Khand-Regular.ttf"
/*------------------------------------------------------------------------------
 * Variable
 *----------------------------------------------------------------------------*/

extern vehicle_t t;
static unsigned int speed = 1;
unsigned int turn_tick = 0;
unsigned int turn_left_count = 0;
unsigned int turn_right_count = 0;



static const SDL_Color COLOR_RED = {.r = 0xff, .g = 0x00, .b = 0x00, .unused = 0x00};
static const SDL_Color COLOR_WHITE = {.r = 0xff, .g = 0xff, .b = 0xff, .unused = 0x00};
static gui_number *cspeed;
static gui_number *codo_number;
static gui_number *ctrip_number;




static gui_image *icon_abs;
static gui_image *icon_high_beam;
static gui_image *icon_low_beam;
static gui_image *icon_warning;
static gui_image *icon_brake;
static gui_image *icon_engine;
static gui_image *icon_motoroil;
static gui_image *icon_battery;
static gui_image *icon_water_temp;
static gui_image *icon_fuel;
static gui_image *cleft_light;
static gui_image *cright_light;

/*------------------------------------------------------------------------------
 * Surface
 *----------------------------------------------------------------------------*/
static SDL_Surface *screen  = NULL;
static SDL_Surface *bg_full = NULL;
static SDL_Surface *bg_comb = NULL;
static SDL_Surface *background = NULL;
static SDL_Surface *backdeco = NULL;
//static SDL_Color tcolor = { 255, 255, 255 ,0};
//static SDL_Color rcolor = {255, 0 , 0 , 0};
//static SDL_Surface *num_surface = NULL;

//static SDL_Surface *high_beam_on = NULL;
//static SDL_Surface *low_beam_on = NULL;
//static SDL_Surface *warning_light_on = NULL;
//static SDL_Surface *abs_on = NULL;
//static SDL_Surface *brake_light_on = NULL;

//static SDL_Surface *engin_light_on = NULL;
//static SDL_Surface *motor_oil_on = NULL;
//static SDL_Surface *battery_on = NULL;

//static SDL_Surface *temperature_light_on = NULL;
static SDL_Surface *temperature_scale = NULL;
static SDL_Surface *temperature_full = NULL;

//static SDL_Surface *fuel_on = NULL;
static SDL_Surface *fuel_scale = NULL;
static SDL_Surface *fuel_full = NULL;



static SDL_Surface *rpm_scale = NULL;
static SDL_Surface *rpm_full = NULL;

static SDL_Surface *decoration_scale = NULL;

//static SDL_Surface *left_light_on = NULL;
//static SDL_Surface *right_light_on = NULL;
//static SDL_Surface *left_light_off = NULL;
//static SDL_Surface *right_light_off = NULL;

//kevin 2018/01/02 ttf
static TTF_Font *font = NULL;

static TTF_Font *temperature_font = NULL;
static TTF_Font *fuel_font = NULL;
static TTF_Font *fuel_ffont = NULL;
static TTF_Font *rpm_font = NULL;
static TTF_Font *rpm_unit_font = NULL;
static TTF_Font *kmh_font = NULL;
static TTF_Font *time_font = NULL;
static TTF_Font *kms_num_font = NULL;

static SDL_Surface *odo = NULL;
static SDL_Surface *trip = NULL;

static SDL_Surface *kms_ttf = NULL;

static SDL_Surface *onetwozero_ttf = NULL;
static SDL_Surface *eighty_ttf = NULL;
static SDL_Surface *fourty_ttf = NULL;

static SDL_Surface *fuel_empty_ttf = NULL;
static SDL_Surface *fuel_half_ttf = NULL;
static SDL_Surface *fuel_full_ttf = NULL;

static SDL_Surface *rpm_unit_ttf = NULL;
static SDL_Surface *rpm_ttf = NULL;
static SDL_Surface *kmh_ttf = NULL;

//kevin 2018/01/09
static SDL_Surface *time_hour_ttf = NULL;
static SDL_Surface *time_min_ttf = NULL;
static SDL_Surface *time_symbol_ttf = NULL;



/*------------------------------------------------------------------------------
 * Function
 *----------------------------------------------------------------------------*/
static bool load_files()
{

    /*------------------------------------------------------------------------------
     * load light on pics
     *----------------------------------------------------------------------------*/
    bg_full = load_image("image/background/bg_full.png");
    //kevin 2018/01/25
    bg_comb = load_image("image/background/bg_full.png");
    //
    background = load_image("image/background/bg_circle light.png");
    backdeco = load_image("image/component/comp_decoration.png");
//    high_beam_on = load_image("image/icon/icn_tell_high beam.png");
//    low_beam_on =load_image("image/icon/icn_tell_low beam.png");
//    warning_light_on =load_image("image/icon/icn_tell_turn signals.png");
//    abs_on = load_image("image/icon/icn_tell_abs.png");
//    brake_light_on =load_image("image/icon/icn_tell_brake system malfunction.png");

//    engin_light_on =load_image("image/icon/icn_tell_engine.png");
//    motor_oil_on = load_image("image/icon/icn_tell_engine oil.png");
//    battery_on = load_image("image/icon/icn_tell_battery.png");

//    temperature_light_on = load_image("image/icon/icn_engine coolant temperature.png");
    temperature_scale =load_image("image/component/comp_scale_engine coolant temperature.png");
    temperature_full = load_image("image/component/comp_engine coolant temperature_08.png");

//    fuel_on =load_image("image/icon/icn_fuel.png");
    fuel_scale =load_image("image/component/comp_scale_battery.png");
    fuel_full = load_image("image/component/comp_battery_01.png");


    rpm_scale =load_image("image/component/comp_scale_rpm.png");
    rpm_full = load_image("image/component/comp_rpm_08.png");

    decoration_scale =load_image("image/component/comp_decoration_scale.png");

    return true;
}

static bool load_ttf()
{

    /*------------------------------------------------------------------------------
     * load ttf
     *----------------------------------------------------------------------------*/


    font = TTF_OpenFont( "ttf/Open_Sans/OpenSans-SemiBold.ttf", 20 );
    temperature_font = TTF_OpenFont("ttf/Khand/Khand-Regular.ttf",20);
    fuel_font = TTF_OpenFont( "ttf/Open_Sans/OpenSans-SemiBold.ttf", 20 );
    fuel_ffont = TTF_OpenFont("ttf/Open_Sans/OpenSans-Regular.ttf",20);
    rpm_font = TTF_OpenFont("ttf/Open_Sans/OpenSans-Light.ttf",20);
    rpm_unit_font = TTF_OpenFont("ttf/Khand/Khand-Regular.ttf",22);
    kmh_font = TTF_OpenFont("ttf/Open_Sans/OpenSans-Light.ttf",20);
    time_font = TTF_OpenFont("ttf/Khand/Khand-Regular.ttf",26);
    kms_num_font = TTF_OpenFont("ttf/Khand/Khand-Regular.ttf",24);

    //TTF_RenderUTF8_Blended(kms_num_font, "152482.8", tcolor);
    //static kms_num_ttf_sec = TTF_RenderUTF8_Blended(kms_num_font, "1354", tcolor);
    //static kms_num_ttf_trd = TTF_RenderUTF8_Blended(kms_num_font, "9824", tcolor);
    odo =  TTF_RenderText_Blended( font, "ODO", COLOR_WHITE );
    trip = TTF_RenderText_Blended( font, "TRIP", COLOR_WHITE );



    onetwozero_ttf = TTF_RenderUTF8_Blended(temperature_font, "120°C", COLOR_RED);
    eighty_ttf = TTF_RenderUTF8_Blended(temperature_font, "80°C", COLOR_WHITE);
    fourty_ttf = TTF_RenderUTF8_Blended(temperature_font, "40°C", COLOR_WHITE);

    fuel_empty_ttf = TTF_RenderUTF8_Blended(fuel_font, "E", COLOR_RED);
    fuel_half_ttf = TTF_RenderUTF8_Blended(temperature_font, "1/2", COLOR_WHITE);
    fuel_full_ttf = TTF_RenderUTF8_Blended(fuel_ffont, "F", COLOR_WHITE);

    rpm_ttf = TTF_RenderUTF8_Blended(rpm_font, "RPM", COLOR_WHITE);
    rpm_unit_ttf = TTF_RenderUTF8_Blended(rpm_font, "1000",COLOR_WHITE);
    kmh_ttf = TTF_RenderUTF8_Blended(kmh_font,"KM/H", COLOR_WHITE);

//    kms_num_ttf_first = TTF_RenderUTF8_Blended(kms_num_font, "152482.8", tcolor);
//    kms_num_ttf_sec = TTF_RenderUTF8_Blended(kms_num_font, "1354", tcolor);
//    kms_num_ttf_trd = TTF_RenderUTF8_Blended(kms_num_font, "9824", tcolor);


    kms_ttf = load_text("ttf/Open_Sans/OpenSans-Light.ttf", 15,"kms" ,COLOR_WHITE);

    time_symbol_ttf = load_text("ttf/Khand/Khand-Regular.ttf", 26, ":" , COLOR_WHITE);



    return true;
}







void apply_icon_surface()
{
    //TIME surface
    static unsigned int time_ticks = SDL_GetTicks();
    if(SDL_GetTicks() - time_ticks > 30000)
    {

    if(time_hour_ttf != NULL)
    {SDL_FreeSurface(time_hour_ttf);}

    if(time_min_ttf != NULL)
    {SDL_FreeSurface(time_min_ttf);}


    time_hour_ttf = TTF_RenderUTF8_Blended(time_font,get_hour_char(), COLOR_WHITE);
    time_min_ttf = TTF_RenderUTF8_Blended(time_font, get_min_char(), COLOR_RED);
    set_icon(370, 6, time_hour_ttf, bg_comb, screen, true);
    set_icon(400, 6, time_min_ttf, bg_comb, screen, true);

    time_ticks = 0;
}
}
//2018/01/18 kevin
void apply_static_background()
{
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 0 ) );
    apply_surface(0, 0, bg_full, screen, NULL);

    apply_surface(220, 60 , background, screen, NULL);
    apply_surface(120, 285, backdeco, screen, NULL);
    apply_surface(190, 30 , decoration_scale, screen, NULL);
    apply_surface(38 , 282, temperature_scale, screen, NULL );
    apply_surface(200, 110, rpm_scale, screen, NULL);
    apply_surface(642, 282, fuel_scale, screen, NULL );

    apply_surface(295, 391, odo, screen, NULL);
    apply_surface(465, 391, trip, screen, NULL);
    apply_surface(333, 425, kms_ttf, screen, NULL );
    apply_surface(498, 425, kms_ttf, screen, NULL );


    apply_surface(88 , 287, onetwozero_ttf, screen, NULL);
    apply_surface(109, 350, eighty_ttf, screen, NULL);
    apply_surface(140, 405, fourty_ttf, screen, NULL);

    apply_surface(648, 409, fuel_empty_ttf, screen, NULL);
    apply_surface(669, 350, fuel_half_ttf, screen, NULL);
    apply_surface(701, 291, fuel_full_ttf, screen, NULL);

    apply_surface(327, 310, rpm_ttf, screen, NULL);
    apply_surface(283, 310, rpm_unit_ttf, screen, NULL);
    apply_surface(472, 310, kmh_ttf, screen, NULL);
    apply_surface(395, 6  , time_symbol_ttf, screen, NULL);




    //kevin 2018/01/25 background combination
    printf("bg_comb = %d\n", bg_comb);

    apply_surface(220, 60 , background, bg_comb, NULL);
    apply_surface(120, 285, backdeco, bg_comb, NULL);
    apply_surface(190, 30 , decoration_scale, bg_comb, NULL);
    apply_surface(38 , 282, temperature_scale, bg_comb, NULL );
    apply_surface(200, 110, rpm_scale, bg_comb, NULL);
    apply_surface(642, 282, fuel_scale, bg_comb, NULL );


    apply_surface(295, 391, odo , bg_comb, NULL);
    apply_surface(465, 391, trip , bg_comb , NULL);
    apply_surface(333, 425, kms_ttf, bg_comb, NULL );
    apply_surface(498, 425, kms_ttf, bg_comb, NULL );


    apply_surface(88 , 287, onetwozero_ttf , bg_comb, NULL);
    apply_surface(109, 350, eighty_ttf , bg_comb, NULL);
    apply_surface(140, 405, fourty_ttf , bg_comb, NULL);

    apply_surface(648, 409, fuel_empty_ttf , bg_comb, NULL);
    apply_surface(669, 350, fuel_half_ttf , bg_comb, NULL);
    apply_surface(701, 291, fuel_full_ttf , bg_comb, NULL);

    apply_surface(327, 310, rpm_ttf, bg_comb, NULL);
    apply_surface(283, 310, rpm_unit_ttf, bg_comb, NULL);
    apply_surface(472, 310, kmh_ttf, bg_comb, NULL);



  /*  apply_surface(240, 419, kms_num_ttf_first, bg_comb, NULL);
    apply_surface(443, 419, kms_num_ttf_sec, bg_comb, NULL)*/;

}



void home_loop()
{
    t.dynamic.speed = (t.dynamic.speed+1)%200;
//        t.dynamic.speed= 10;
    if (manager_current_page() != e_page_home) return;

//    apply_icon_surface();

//    c_speed(CMODE_LOOP, t.dynamic.speed);


    static int b = 1111;
    static int c = 2222;

    cspeed->update(t.dynamic.speed);
    codo_number->update(b);
    ctrip_number->update(c);

    static unsigned char a;

    icon_abs->update(++a%20 > 10);
    icon_high_beam->update(true);
    icon_low_beam->update(true);
    icon_warning->update(true);
    icon_brake->update(true);
    icon_engine->update(true);
    icon_motoroil->update(true);
    icon_battery->update(true);
    icon_water_temp->update(true);
    icon_fuel->update(true);
    cleft_light->update(true);
    cright_light->update(true);
}

bool home_init(SDL_Surface *surface)
{
    turn_tick = SDL_GetTicks();

    screen = surface;

    load_files();

    load_ttf();

    //2018/01/18 kevin
    apply_static_background();

//    cspeed = new gui_number(screen, bg_comb, 380, 80, FONT_KHAND_SEMIBOLD, COLOR_WHITE, 120, 0);
    cspeed = new gui_number(screen, bg_comb, 293, 100, 228, 126,
                          gui_text::align_center, FONT_KHAND_SEMIBOLD,
                          COLOR_WHITE, 180);
    codo_number = new gui_number(screen, bg_comb, 275, 415, 73, 36,
                                 gui_text::align_center, FONT_KHAND_REGULAR,
                                 COLOR_WHITE, 24);
    ctrip_number = new gui_number(screen, bg_comb, 450, 415, 42, 36,
                                  gui_text::align_center, FONT_KHAND_REGULAR,
                                  COLOR_WHITE, 24);

    cleft_light = new gui_image(screen, bg_comb, 0, 4, "./image/component/left_light_all.png");
    cright_light = new gui_image(screen, bg_comb, 620, 4, "./image/component/right_light_all.png");


    icon_abs = new gui_image(screen, bg_comb, 80, 108, "./image/icon/icn_tell_abs.png");
    icon_high_beam = new gui_image(screen, bg_comb, 80, 50, "./image/icon/icn_tell_high beam.png");
    icon_low_beam = new gui_image(screen, bg_comb, 80, 50, "./image/icon/icn_tell_low beam.png");
    icon_warning = new gui_image(screen, bg_comb, 138, 50, "./image/icon/icn_tell_turn signals.png");
    icon_brake = new gui_image(screen, bg_comb, 138, 108, "./image/icon/icn_tell_brake system malfunction.png");
    icon_engine = new gui_image(screen, bg_comb, 612, 50, "./image/icon/icn_tell_engine.png");
    icon_motoroil = new gui_image(screen, bg_comb, 670, 50, "./image/icon/icn_tell_engine oil.png");
    icon_battery = new gui_image(screen, bg_comb, 670, 108, "./image/icon/icn_tell_battery.png");
    icon_water_temp = new gui_image(screen, bg_comb, 154, 335, "./image/icon/icn_engine coolant temperature.png");
    icon_fuel = new gui_image(screen, bg_comb, 612, 335, "./image/icon/icn_fuel.png");



    return true;
}

//kevin 2017/12/27
bool home_deinit()
{
//    c_speed(CMODE_DEINIT, t.dynamic.speed);

    delete(cspeed);
    delete(codo_number);
    delete(ctrip_number);
    delete(cleft_light);
    delete(cright_light);
    delete(icon_abs);
    delete(icon_battery);
    delete(icon_brake);
    delete(icon_engine);
    delete(icon_fuel);
    delete(icon_high_beam);
    delete(icon_low_beam);
    delete(icon_motoroil);
    delete(icon_warning);
    delete(icon_water_temp);

//    SDL_FreeSurface(num_surface);



//    SDL_FreeSurface(high_beam_on);
//    SDL_FreeSurface(low_beam_on);
//    SDL_FreeSurface(warning_light_on);
//    SDL_FreeSurface(abs_on);
//    SDL_FreeSurface(brake_light_on);
//    SDL_FreeSurface(engin_light_on);
//    SDL_FreeSurface(motor_oil_on);
//    SDL_FreeSurface(battery_on);
//    SDL_FreeSurface(temperature_light_on);
//    SDL_FreeSurface(temperature_scale);
//    SDL_FreeSurface(fuel_on);
//    SDL_FreeSurface(fuel_scale);
//    SDL_FreeSurface(rpm_scale);
//    SDL_FreeSurface(decoration_scale);
//    SDL_FreeSurface(left_light_on);
//    SDL_FreeSurface(right_light_on);
//    SDL_FreeSurface(left_light_off);
//    SDL_FreeSurface(right_light_off);
//    SDL_FreeSurface(odo);
    TTF_CloseFont( font );



    return 1;
}

void home_handle_input(uint8_t type, SDLKey key)
{
    if (manager_current_page() != e_page_home) return;


    //If a key was pressed
    if(type == SDL_KEYDOWN )
    {
        printf("%s\n\n", __func__);


        //Adjust the num
        switch( key )
        {
        case SDLK_UP : ++speed; break;
        case SDLK_DOWN : --speed; break;
        default : break;
        }
    }
}




void home_handle_ipc(char *from, char *d, size_t l)
{
    (void)(from); (void)(l);

    switch (d[0]) {
    case 'S':
        speed = strtol(&d[1], NULL, 10);
        break;
    default:
        break;
    }
}
