/******************************************************************************
 * file         vehicle.c
 * date         2017.09.17
 * name         xzhong
 * note
 *****************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <auo/global.h>
#include <auo/busx.h>
#include "vehicle.h"

inline ssize_t vehicle_cmd(sender_t sender, VEHICLE_ID_t id, char *d, size_t l)
{
    char b[256] = {0x00};

    b[0] = PROTOCOL_GRP_VEHICLE;
    b[1] = id;
    memcpy(&b[2], d, l);

    return sender(b, 2+l);
}

inline ssize_t vehicle_msg(sender_t sender, VEHICLE_ID_t id, char *d, size_t l)
{
    return vehicle_cmd(sender, id, d, l);
}

#if (__VEHICLE_VER__ == 1)
int vehicle_parser(char *d, size_t l, vehicle_t *t)
{
    (void)l;

    VEHICLE_ID_t id = (VEHICLE_ID_t)d[1];

    void*        p;
    uchar        s;

    switch (id) {

    //SYNC
    case VEHICLE_ID_SYNC:
        return id;
        break;

    //IGNITION
    case VEHICLE_ID_SYSTEM:
        return id;
        break;
    case VEHICLE_ID_SYSTEM_IGNITION:
        p = &t->system.ingition;
        s = sizeof(t->system.ingition);
        break;
    case VEHICLE_ID_SYSTEM_COUNTRY:
        p = &t->system.country;
        s = sizeof(t->system.country);
        break;
    case VEHICLE_ID_SYSTEM_DATE:
        p = &t->system.date;
        s = sizeof(t->system.date);
        break;
    case VEHICLE_ID_SYSTEM_TIME:
        p = &t->system.time;
        s = sizeof(t->system.time);
        break;
    case VEHICLE_ID_SYSTEM_DISPLAY_MODE:
        p = &t->system.display_mode;
        s = sizeof(t->system.display_mode);
        break;
    case VEHICLE_ID_SYSTEM_POSITION:
        p = &t->system.position;
        s = sizeof(t->system.position);
        break;

    //DYNAMIC
    case VEHICLE_ID_DYNAMIC:
        return id;
        break;
    case VEHICLE_ID_DYNAMIC_SPEED:
        p = &t->dynamic.speed;
        s = sizeof(t->dynamic.speed);
        break;
    case VEHICLE_ID_DYNAMIC_TACHO:
        p = &t->dynamic.tacho;
        s = sizeof(t->dynamic.tacho);
        break;
    case VEHICLE_ID_DYNAMIC_ODO:
        p = &t->dynamic.odo;
        s = sizeof(t->dynamic.odo);
        break;
    case VEHICLE_ID_DYNAMIC_TRIP:
        p = &t->dynamic.trip;
        s = sizeof(t->dynamic.trip);
        break;
    case VEHICLE_ID_DYNAMIC_REMAIN:
        p = &t->dynamic.remain;
        s = sizeof(t->dynamic.remain);
        break;
    case VEHICLE_ID_DYNAMIC_TURN:
        p = &t->dynamic.turn;
        s = sizeof(t->dynamic.turn);
        break;
    case VEHICLE_ID_DYNAMIC_GEAR:
        p = &t->dynamic.gear;
        s = sizeof(t->dynamic.gear);
        break;
    case VEHICLE_ID_DYNAMIC_DRIVE_MODE:
        p = &t->dynamic.drive_mode;
        s = sizeof(t->dynamic.drive_mode);
        break;
    case VEHICLE_ID_DYNAMIC_LEAN_ANGLE:
        p = &t->dynamic.lean_angle;
        s = sizeof(t->dynamic.lean_angle);
        break;
    case VEHICLE_ID_DYNAMIC_G_FORCE:
        p = &t->dynamic.gforce;
        s = sizeof(t->dynamic.gforce);
        break;

        //BATTERY
    case VEHICLE_ID_BATTERY:
        return id;
        break;
    case VEHICLE_ID_BATTERY_VOLTAGE:
        p = &t->battery.voltage;
        s = sizeof(t->battery.voltage);
        break;
    case VEHICLE_ID_BATTERY_CAPACITY:
        p = &t->battery.capacity;
        s = sizeof(t->battery.capacity);
        break;
    case VEHICLE_ID_BATTERY_TEMPERATURE:
        p = &t->battery.temperature;
        s = sizeof(t->battery.temperature);
        break;
    case VEHICLE_ID_BATTERY_CHARGER:
        p = &t->battery.charger;
        s = sizeof(t->battery.charger);
        break;

        //SENSOR
    case VEHICLE_ID_SENSOR:
        return id;
        break;
    case VEHICLE_ID_SENSOR_FUEL:
        p = &t->sensor.fuel;
        s = sizeof(t->sensor.fuel);
        break;
    case VEHICLE_ID_SENSOR_AMBIENT_LIGHT:
        p = &t->sensor.ambient_light;
        s = sizeof(t->sensor.ambient_light);
        break;
    case VEHICLE_ID_SENSOR_AMBIENT_TEMPERATURE:
        p = &t->sensor.ambient_temperature;
        s = sizeof(t->sensor.ambient_temperature);
        break;
    case VEHICLE_ID_SENSOR_WATER_TEMPERATURE:
        p = &t->sensor.water_temperature;
        s = sizeof(t->sensor.water_temperature);
        break;
    case VEHICLE_ID_SENSOR_OIL_TEMPERATURE:
        p = &t->sensor.oil_temperature;
        s = sizeof(t->sensor.oil_temperature);
        break;

        //SYMBOL0
    case VEHICLE_ID_SYMBOL0:
        return id;
        break;
    case VEHICLE_ID_SYMBOL0_HEAD_LIGHT:
    {
        vehicle_symbol0_t *x = (vehicle_symbol0_t*)&d[2];

        if (t->symbol0.head_light != x->head_light)
        {
            t->symbol0.head_light = x->head_light;
            return id;
        }
    }   break;
    case VEHICLE_ID_SYMBOL0_FOG_LIGHT:
    {
        vehicle_symbol0_t *x = (vehicle_symbol0_t*)&d[2];

        if (t->symbol0.fog_light != x->fog_light)
        {
            t->symbol0.fog_light = x->fog_light;
            return id;
        }
    }   break;
    case VEHICLE_ID_SYMBOL0_OIL:
    {
        vehicle_symbol0_t *x = (vehicle_symbol0_t*)&d[2];

        if (t->symbol0.oil != x->oil)
        {
            t->symbol0.oil = x->oil;
            return id;
        }
    }   break;
    case VEHICLE_ID_SYMBOL0_FUEL:
    {
        vehicle_symbol0_t *x = (vehicle_symbol0_t*)&d[2];

        if (t->symbol0.fuel != x->fuel)
        {
            t->symbol0.fuel = x->fuel;
            return id;
        }
    }   break;
    case VEHICLE_ID_SYMBOL0_ENGINE:
    {
        vehicle_symbol0_t *x = (vehicle_symbol0_t*)&d[2];

        if (t->symbol0.engine != x->engine)
        {
            t->symbol0.engine = x->engine;
            return id;
        }
    }   break;
    case VEHICLE_ID_SYMBOL0_BATTERY:
    {
        vehicle_symbol0_t *x = (vehicle_symbol0_t*)&d[2];

        if (t->symbol0.battery != x->battery)
        {
            t->symbol0.battery = x->battery;
            return id;
        }
    }   break;

    default:
        return -1;
    }

    if (memcmp(p, &d[2], s))
    {
        memcpy(p, &d[2], s);
        return id;
    }

    return -1;
}
#endif // __VEHICLE_VER__ == 0

