#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>
#include<string>
#include<iostream>
#include<sstream>

//data protocol 2018/01/23
#include "vehicle.h"
#include "global.h"





#include "manager.h"

#include "home.h"



/*------------------------------------------------------------------------------
 * Variable
 *----------------------------------------------------------------------------*/
static SDL_Surface      *screen         = NULL;
static e_page           current_page;

static int              frame_rate      = 10;
static bool             demo            = false;
//2018/01/23 kevin
//2018/01/23 kevin
vehicle_t t;
extern bool leftFlag;
extern bool rightFlag;
extern bool bwarning;
extern bool babs;
extern bool bbrake;
extern bool bengin;
extern bool bmotor_oil;
extern bool bbattery;
extern bool btemp_light;
extern bool bfuel;
extern bool beam;
extern bool Pspeed;
extern bool Podo;
extern bool Ptrip;







#define FLIP_TIMEOUT    (1000/frame_rate)


/*------------------------------------------------------------------------------
 * Function
 *----------------------------------------------------------------------------*/
static void event_handler(SDL_Event *e)
{
    if (e->type == SDL_KEYDOWN)
    {
        switch( e->key.keysym.sym )
        {
        case SDLK_LEFT:
            current_page = (e_page)((current_page+1)%e_page_max);
            break;
        case SDLK_RIGHT:
            current_page = (e_page)((current_page+e_page_max-1)%e_page_max);
            break;

        case SDLK_d:
            demo = !demo;
            break;
        default:
            break;
        }
    }

    printf("%s > current_page:%d\n", __func__, current_page);

}

e_page manager_current_page()
{
    return current_page;
}

bool manager_is_demo()
{
    return demo;
}

int manager_init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)== -1)
    {
        return -1;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH , SCREEN_HEIGHT , SCREEN_BPP , SDL_SWSURFACE );

    if(screen == NULL )
    {
        printf("%s > screen NULL\n", __func__);
        return -1;
    }
    //kevin 2018/01/02 ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    if(home_init(screen) == false)
    {
        return -1;
    }

    SDL_WM_SetCaption( "ADIVA UI", "ADIVA UI" );

    return 0;
}








//extern bool leftFlag = 1;
//extern bool rightFlag = 1;
//extern bool bwarning = 1;
//extern bool babs = 1 ;
//extern bool bbrake = 1;
//extern bool bengin = 1;
//extern bool bmotor_oil = 1;
//extern bool bbattery = 1;
//extern bool btemp_light = 1;
//extern bool bfuel = 1;
//extern bool beam = 1;

//kevin data function 2018/01/23
void refresh(void* obj, char *from, char* data, unsigned long len)
{
    (void)(obj); (void)(from); (void)(len); (void)(data);



    //    printf("%s: ", __func__);
    //    for (size_t i = 0; i < len; i++) printf("%02x ", (uchar)data[i]); printf("\n");

    //data[0]   = grp
    //data[1]   = hdr
    //data[2~N] = structure

    uchar grp=(uchar)data[0];
//    uchar hdr=(uchar)data[1];
//    uchar *d=(uchar*)&data[2];

    //    if ((grp == PROTOCOL_GRP_VEHICLE) && (hdr == VEHICLE_ID_CONTROL))
    //    {
    //        printf("%s: ", __func__);
    //        for (size_t i = 0; i < len; i++) printf("%02x ", (uchar)data[i]); printf("\n");
    //    }

    switch((uchar)grp)
    {

//    case PROTOCOL_GRP_SYSTEM:
//        switch(hdr)
//        {
//        case SYSTEM_ID_PM:
//        {
//            system_power_manager_t *x = (system_power_manager_t*)d;

//            m_system.set_power_manager_acc(x->acc);
//            m_system.set_power_manager_power(x->power);
//        }   break;
//        case SYSTEM_ID_RTC:
//        {
//            system_rtc_t *x = (system_rtc_t*)d;

//            m_system.set_rtc_hour(x->hour);
//            m_system.set_rtc_minute(x->minute);
//            m_system.set_rtc_second(x->second);
//            m_system.set_rtc_year(x->year);
//            m_system.set_rtc_month(x->month);
//            m_system.set_rtc_day(x->day);
//            m_system.set_rtc_week(x->week);
//        }   break;
//        case SYSTEM_ID_CONFIG:
//        {
//            system_config_t *x = (system_config_t*)d;

//            m_system.set_config_display_mode(x->display_mode);
//            m_system.set_config_measurement_unit(x->measurement_unit);
//            m_system.set_config_language(x->language);

//            switch (m_system.get_config_language())
//            {
//            case 44:
//                set_language("UK");
//                break;
//            case 39:
//                set_language("Italy");
//                break;
//            case 34:
//                set_language("Spain");
//                break;
//            case 49:
//                set_language("Germany");
//                break;
//            case 84:
//                set_language("Vientnam");
//                break;
//            case 86:
//                set_language("China");
//                break;
//            case 886:
//                set_language("Taiwan");
//                break;
//            default:
//                set_language("");
//                break;
//            }

//        }   break;
//        default:
//            break;
//        }
//        break;

//    case PROTOCOL_GRP_HMI:
//        switch(hdr)
//        {
//        case HMI_ID_KEY:
//        {
//            hmi_key_t *x = (hmi_key_t*)d;

//            m_hmi.set_hmi_key_from(x->from);
//            m_hmi.set_hmi_key_type(x->type);
//            m_hmi.set_hmi_key_event(x->event);
//            m_hmi.set_hmi_key_code(x->code);

//            switch (m_hmi.get_hmi_key_code())
//            {
//            case KEY_LEFF:
//                if(get_leftLight() == 0 && get_rightLight() == 0 )
//                {
//                    if(m_hmi.get_hmi_key_event() == KEY_EVENT_PRESS)
//                    {
//                        if(get_pageIndexSwitch() == false && get_trFlag() == false)
//                        {
//                            // gsound_play('7','0',(char*)"transform.wav");
//                            if(get_currentPageIndex() == 1 && get_iconMessage() == 1)
//                            {
//                                set_iconMessage(0);
//                            }
//                            set_pageIndexSwitch(true);
//                        }
//                    }
//                }
//                break;
//            case KEY_FACEBOOK_LIVE:
//                if(m_hmi.get_hmi_key_event() == KEY_EVENT_PRESS)
//                {
//                    //                    live_cmd_run(dashboard_send_live, LIVE_MODE_FACEBOOK, NULL);
//                }
//                break;
//            default:
//                break;
//            }

//        }   break;
//        default:
//            break;
//        }

//        break;
//    case PROTOCOL_GRP_AUDIO:
//        break;
//    case PROTOCOL_GRP_VIDEO:
//        break;
    case PROTOCOL_GRP_VEHICLE:

        switch(vehicle_parser(data,len,&t))
        {
//        case VEHICLE_ID_SYSTEM_IGNITION:
//        {
//                m_vehicle.set_ignition(t.system.ingition);
//        }   break;
//        case VEHICLE_ID_SYSTEM_COUNTRY:
//        {
//                m_vehicle.set_country_code(t.system.country);
//        }   break;
//        case VEHICLE_ID_SYSTEM_DATE:
//        {
//            {
//                m_vehicle.set_date_day(t.system.date.day);
//                m_vehicle.set_date_month(t.system.date.month);
//                m_vehicle.set_date_week(t.system.date.week);
//                m_vehicle.set_date_year(t.system.date.year);
//            }
//        }   break;
//        case VEHICLE_ID_SYSTEM_TIME:
//        {
//            {
//                m_vehicle.set_time_hour(t.system.time.hour);
//                m_vehicle.set_time_minute(t.system.time.minute);
//                m_vehicle.set_time_second(t.system.time.second);
//            }
//        }   break;
//        case VEHICLE_ID_SYSTEM_DISPLAY_MODE:
//        {
//                m_vehicle.set_display_mode(t.system.display_mode);

//        }   break;
//        case VEHICLE_ID_SYSTEM_POSITION:
//        {
//            {
//                m_vehicle.set_position_latitude(t.system.position.latitude);
//                m_vehicle.set_position_longitude(t.system.position.longitude);
//            }
//        }   break;
        case VEHICLE_ID_DYNAMIC_SPEED:
        {
            printf("case VEHICLE_ID_DYNAMIC_SPEED!!!\n");


        }   break;
//        case VEHICLE_ID_DYNAMIC_TACHO:
//        {
//                m_vehicle.set_tacho(t.dynamic.tacho);
//            //            vehicle_dynamic_t *x= (vehicle_dynamic_t*)d;
//            //            m_vehicle.set_tacho(x->tacho);
//        }   break;
//        case VEHICLE_ID_DYNAMIC_ODO:
//        {
//                m_vehicle.set_odo(t.dynamic.odo);
//        }   break;
//        case VEHICLE_ID_DYNAMIC_TRIP:
//        {
//                m_vehicle.set_trip(t.dynamic.trip);
//        }   break;
//        case VEHICLE_ID_DYNAMIC_REMAIN:
//        {
//                m_vehicle.set_remain(t.dynamic.remain);
//        }   break;
//        case VEHICLE_ID_DYNAMIC_TURN:
//        {
//            {
//                m_vehicle.set_turn_blink(t.dynamic.turn.blink);
//                m_vehicle.set_turn_mode(t.dynamic.turn.mode);
//            }
//        }   break;
//        case VEHICLE_ID_DYNAMIC_GEAR:
//        {
//            {
//                m_vehicle.set_gear_mode(t.dynamic.gear.mode);
//                m_vehicle.set_gear_text(t.dynamic.gear.text);
//            }
//        }   break;
//        case VEHICLE_ID_DYNAMIC_DRIVE_MODE:
//        {
//                m_vehicle.set_drive_mode(t.dynamic.drive_mode);
//        }   break;
//        case VEHICLE_ID_DYNAMIC_LEAN_ANGLE:
//        {
//            {
//                m_vehicle.set_lean_angle(t.dynamic.lean_angle);
//            }
//        }   break;
//        case VEHICLE_ID_DYNAMIC_G_FORCE:
//        {
//            {
//                m_vehicle.set_gforce_accel(t.dynamic.gforce.g_accel);
//                m_vehicle.set_gforce_break(t.dynamic.gforce.g_break);
//                m_vehicle.set_gforce_left(t.dynamic.gforce.g_left);
//                m_vehicle.set_gforce_right(t.dynamic.gforce.g_right);
//            }
//        }   break;
//        case VEHICLE_ID_BATTERY_VOLTAGE:
//        {
//            bbattery = true;
//        }   break;
//        case VEHICLE_ID_BATTERY_CAPACITY:
//        {
//            m_vehicle.set_battery_capacity(t.battery.capacity);
//        }   break;
//        case VEHICLE_ID_BATTERY_TEMPERATURE:
//        {
//            btemp = true;
//        }   break;
//        case VEHICLE_ID_BATTERY_CHARGER:
//        {
//            m_vehicle.set_battery_charger_mode(t.battery.charger);
//        }   break;
//        case VEHICLE_ID_SENSOR_FUEL:
//        {
//            bfuel = true;
//        }   break;
//        case VEHICLE_ID_SENSOR_AMBIENT_LIGHT:
//        {
//            m_vehicle.set_ambient_light(t.sensor.ambient_light);
//        }   break;
//        case VEHICLE_ID_SENSOR_AMBIENT_TEMPERATURE:
//        {
//            m_vehicle.set_ambient_temperature(t.sensor.ambient_temperature);
//        }   break;
//        case VEHICLE_ID_SENSOR_WATER_TEMPERATURE:
//        {
//            m_vehicle.set_water_temperature(t.sensor.water_temperature);
//        }   break;
//        case VEHICLE_ID_SENSOR_OIL_TEMPERATURE:
//        {
//            m_vehicle.set_oil_temperature(t.sensor.oil_temperature);
//        }   break;
//        case VEHICLE_ID_SYMBOL0_HEAD_LIGHT:
//        {
//            m_vehicle.set_symbol_battery(t.symbol0.head_light);
//        }   break;
//        case VEHICLE_ID_SYMBOL0_FOG_LIGHT:
//        {
//            m_vehicle.set_symbol_fog_light(t.symbol0.fog_light);
//        }   break;
//        case VEHICLE_ID_SYMBOL0_OIL:
//        {
//            m_vehicle.set_symbol_oil(t.symbol0.oil);
//        }   break;
//        case VEHICLE_ID_SYMBOL0_FUEL:
//        {
//            m_vehicle.set_symbol_fuel(t.symbol0.fuel);
//        }   break;
//        case VEHICLE_ID_SYMBOL0_ENGINE:
//        {
//            bengine = true;
//        }   break;
//        case VEHICLE_ID_SYMBOL0_BATTERY:
//        {
//            m_vehicle.set_symbol_battery(t.symbol0.battery);
//        }   break;

        default:
            break;
        }

        break;
//    case PROTOCOL_GRP_SNAVI:
//        switch(hdr)
//        {
//        case SNAVI_ID_STATUS:
//        {
//            snavi_status_t *x = (snavi_status_t*)d;

//            m_snavi.set_status_speed(x->speed);
//            m_snavi.set_status_destination_distance(x->destination_distance);
//            m_snavi.set_status_turn_distance(x->turn_distance);
//        }   break;

//        case SNAVI_ID_DESTINATION:
//        {
//            snavi_destination_t *x = (snavi_destination_t*)d;

//            m_snavi.set_destination_addr(x->addr);
//        }   break;
//        case SNAVI_ID_TURN:
//        {
//            snavi_turn_t *x = (snavi_turn_t*)d;

//            m_snavi.set_turn_icon(x->icon);
//            m_snavi.set_turn_addr(x->addr);
//        }   break;
//        default:
//            break;
//        }
//        break;
//    case PROTOCOL_GRP_WEATHER:
//        break;
//    case PROTOCOL_GRP_MESSAGER:
//        switch(hdr)
//        {
//        case MESSAGER_ID_CALL:
//        {
//            messager_call_t *x = (messager_call_t*)d;

//            m_messager.set_call_type(x->type);
//            m_messager.set_call_number(x->number);
//            m_messager.set_call_name(x->name);

//        }   break;

//        case MESSAGER_ID_NOTIFY:
//        {
//            messager_notify_t *x = (messager_notify_t*)d;
//            m_messager.set_notify_year(x->year);
//            m_messager.set_notify_month(x->month);
//            m_messager.set_notify_day(x->day);
//            m_messager.set_notify_hour(x->hour);
//            m_messager.set_notify_minute(x->minute);
//            m_messager.set_notify_count(x->count);

//            m_messager.set_notify_icon(x->icon);
//            m_messager.set_notify_title(x->title);
//            m_messager.set_notify_text(x->text);


//            if(get_currentPageIndex() != 2)
//            {
//                set_iconMessage(1);
//            }
//            else
//            {
//                set_iconMessage(0);
//            }
//            set_messageTopContent(get_messageMiddleContent());
//            set_messageTopIcon(get_messageMiddleIcon());
//            set_messageTopTitle(get_messageMiddleTitle());
//            set_messageTopTime(get_messageMiddleTime());

//            set_messageMiddleContent(get_messageBottomContent());
//            set_messageMiddleIcon(get_messageBottomIcon());
//            set_messageMiddleTitle(get_messageBottomTitle());
//            set_messageMiddleTime(get_messageBottomTime());

//            set_messageBottomContent(m_messager.get_notify_text());
//            set_messageBottomIcon(m_messager.get_notify_icon());
//            set_messageBottomTitle(m_messager.get_notify_title());


//            //            set_messageAnimation(true);


//            if(m_messager.get_notify_minute()<10)
//            {
//                set_messageBottomTime(QString::number(m_messager.get_notify_hour()) + " : 0" + QString::number(m_messager.get_notify_minute()));
//            }
//            else
//            {
//                set_messageBottomTime(QString::number(m_messager.get_notify_hour()) + " : " + QString::number(m_messager.get_notify_minute()));
//            }

//        }   break;
//        default:
//            break;
//        }
//        break;

//    case PROTOCOL_GRP_GPS:
//        break;
//    case PROTOCOL_GRP_WIFI:
//    {
//        switch(hdr)
//        {
//        case WIFI_ID_STATUS:
//        {
//            wifi_status_t *x = (wifi_status_t*)d;

//            m_wifi.set_status_power(x->power);
//            m_wifi.set_status_connection(x->connection);
//            if(m_wifi.get_status_connection() == 1)
//            {
//                set_iconWiFi(1);
//                // gsound_play('3','0',(char*)"wifi_bt.wav");
//            }
//            else
//            {
//                set_iconWiFi(0);
//                // gsound_play('3','0',(char*)"wifi_bt.wav");
//                if(get_currentPageIndex() == 4 && get_leftLight() == 0 && get_rightLight() == 0)
//                {
//                    set_pageIndexSwitch(true);
//                    // gsound_play('7','0',(char*)"transform.wav");
//                }
//            }
//        }   break;
//        default:
//            break;
//        }
//    }   break;
//    case PROTOCOL_GRP_BLUETOOTH:
//    {
//        switch(hdr)
//        {
//        case BLUETOOTH_ID_STATUS:
//        {
//            bluetooth_status_t *x = (bluetooth_status_t*)d;

//            m_bluetooth.set_status_power(x->power);
//            m_bluetooth.set_status_connection(x->connection);
//            if(m_bluetooth.get_status_connection() == 1)
//            {
//                set_iconBT(1);
//                // gsound_play('3','0',(char*)"wifi_bt.wav");
//            }
//            else
//            {
//                set_iconBT(0);
//                // gsound_play('3','0',(char*)"wifi_bt.wav");
//            }
//        }   break;
//        default:
//            break;
//        }
//    }   break;
//    case PROTOCOL_GRP_LIVE:
//        switch(hdr)
//        {
//        case LIVE_ID_STATUS:
//        {
//            live_status_t *x = (live_status_t*)d;

//            m_live.set_status_mode(x->mode);
//            m_live.set_status_url(x->url);
//            if(m_live.get_status_mode() != 0)
//            {
//                set_iconLIVE(1);
//            }
//            else
//            {
//                set_iconLIVE(0);
//            }
//        }   break;
//        default:
//            break;
//        }
//        break;
//    case PROTOCOL_GRP_DVR:
//        break;

//    case PROTOCOL_GRP_UPGRADE:
//        break;
    default:
        break;
    }

    if(data != NULL) free(data);

}








void manager_deinit()
{   
    home_deinit();
    TTF_Quit();
    SDL_Quit();
}

void manager_loop()
{
    static SDL_Event e;

    int ticks = 0;
    int elapse = 0;

    ticks = SDL_GetTicks();


    while( SDL_PollEvent(&e))
    {
        event_handler(&e);

        home_handle_input(e.type, e.key.keysym.sym);

        if(e.type == SDL_QUIT)
        {
            manager_deinit();
            exit(0);
        }
    }


    home_loop();

    //xz: why?
    SDL_UpdateRect(screen,0,0,0,0);

    if (SDL_Flip(screen) == -1)
    {
        printf("%s > SDL_Flip error!\n", __func__);
        //        exit(0);
    }

    elapse = SDL_GetTicks() - ticks;

    if(elapse < FLIP_TIMEOUT)
    {
        SDL_Delay(FLIP_TIMEOUT - elapse);
    }

    printf("elapse:%d\n", elapse);
}


