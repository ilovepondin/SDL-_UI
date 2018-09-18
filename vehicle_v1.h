#ifdef __cplusplus
extern "C" {
#endif

#ifndef __VEHICLE_H__
#define __VEHICLE_H__
/******************************************************************************
 * file         vehicle_v1.h
 * name         xzhong
 * 2018.01.07   fisrt release
 *****************************************************************************/
#include <stdint.h>
#include "global.h"

typedef enum
{
    //SYNC
    VEHICLE_ID_SYNC                         = 0x00,

    //IGNITION
    VEHICLE_ID_SYSTEM                       = 0x10,
    VEHICLE_ID_SYSTEM_IGNITION              = 0x11,
    VEHICLE_ID_SYSTEM_COUNTRY               = 0x12,
    VEHICLE_ID_SYSTEM_DATE                  = 0x13,
    VEHICLE_ID_SYSTEM_TIME                  = 0x14,
    VEHICLE_ID_SYSTEM_DISPLAY_MODE          = 0x15,
    VEHICLE_ID_SYSTEM_POSITION              = 0x16,

    //DYNAMIC
    VEHICLE_ID_DYNAMIC                      = 0x20,
    VEHICLE_ID_DYNAMIC_SPEED                = 0x21,
    VEHICLE_ID_DYNAMIC_TACHO                = 0x22,
    VEHICLE_ID_DYNAMIC_ODO                  = 0x23,
    VEHICLE_ID_DYNAMIC_TRIP                 = 0x24,
    VEHICLE_ID_DYNAMIC_REMAIN               = 0x25,
    VEHICLE_ID_DYNAMIC_TURN                 = 0x26,
    VEHICLE_ID_DYNAMIC_GEAR                 = 0x27,
    VEHICLE_ID_DYNAMIC_DRIVE_MODE           = 0x28,
    VEHICLE_ID_DYNAMIC_LEAN_ANGLE           = 0x29,
    VEHICLE_ID_DYNAMIC_G_FORCE              = 0x2A,

    //BATTERY
    VEHICLE_ID_BATTERY                      = 0x30,
    VEHICLE_ID_BATTERY_VOLTAGE              = 0x31,
    VEHICLE_ID_BATTERY_CAPACITY             = 0x32,
    VEHICLE_ID_BATTERY_TEMPERATURE          = 0x33,
    VEHICLE_ID_BATTERY_CHARGER              = 0x34,

    //SENSOR
    VEHICLE_ID_SENSOR                       = 0x40,
    VEHICLE_ID_SENSOR_FUEL                  = 0x41,
    VEHICLE_ID_SENSOR_AMBIENT_LIGHT         = 0x42,
    VEHICLE_ID_SENSOR_AMBIENT_TEMPERATURE   = 0x43,
    VEHICLE_ID_SENSOR_WATER_TEMPERATURE     = 0x44,
    VEHICLE_ID_SENSOR_OIL_TEMPERATURE       = 0x45,

    //SYMBOL0
    VEHICLE_ID_SYMBOL0                      = 0xF0,
    VEHICLE_ID_SYMBOL0_HEAD_LIGHT           = 0xF1,
    VEHICLE_ID_SYMBOL0_FOG_LIGHT            = 0xF2,
    VEHICLE_ID_SYMBOL0_OIL                  = 0xF3,
    VEHICLE_ID_SYMBOL0_FUEL                 = 0xF4,
    VEHICLE_ID_SYMBOL0_ENGINE               = 0xF5,
    VEHICLE_ID_SYMBOL0_BATTERY              = 0xF6,

} __attribute__ ((__packed__))  VEHICLE_ID_t;


// -----------------------------------------------------------------------------
// System
// -----------------------------------------------------------------------------
typedef enum {
    IGNITION_LOCK               = 0,
    IGNITION_OFF                = 1,
    IGNITION_ACC                = 3,
    IGNITION_ON                 = 4,
    IGNITION_START              = 5,
} __attribute__ ((__packed__))  VEHICLE_IGNITION_t;

/*---------------------------------------------
 * https://en.wikipedia.org/wiki/ISO_3166-1_numeric
 * https://zh.wikipedia.org/wiki/%E5%9C%8B%E5%AE%B6%E5%9C%B0%E5%8D%80%E4%BB%A3%E7%A2%BC
 * ------------------------------------------*/
typedef enum {
    VEHICLE_COUNTRY_China                   = 156,
    VEHICLE_COUNTRY_Taiwan                  = 158,
    VEHICLE_COUNTRY_Germany                 = 276,
    VEHICLE_COUNTRY_Italy                   = 380,
    VEHICLE_COUNTRY_VietNam                 = 704,
    VEHICLE_COUNTRY_Spain                   = 724,
    VEHICLE_COUNTRY_UnitedKingdom           = 826,

    VEHICLE_COUNTRY_MAX                     = 0xFFFF
} __attribute__ ((__packed__))  VEHICLE_COUNTRY_t;

typedef struct {
    ushort                      year;
    uchar                       month;
    uchar                       day;
    uchar                       week;
} __attribute__ ((__packed__))  vehicle_date_t;

typedef struct {
    uchar                       hour;
    uchar                       minute;
    uchar                       second;
} __attribute__ ((__packed__))  vehicle_time_t;

typedef enum {
    VEHICLE_DISPLAY_MODE_DAY    = 0x00,
    VEHICLE_DISPLAY_MODE_NIGHT  = 0x01,
    VEHICLE_DISPLAY_MODE_AUTO   = 0x02
} __attribute__ ((__packed__))  VEHICLE_DISPLAY_MODE_t;


typedef struct {
    int                       latitude;               //range -180000000 ~ +180000000
                                                        //unit  0.000001°
                                                        //ex    123123456=123.123456°
    int                       longitude;              //range -180000000 ~ +180000000
                                                        //unit  0.000001°
                                                        //ex    123123456=123.123456°
} __attribute__ ((__packed__))  vehicle_position_t;


//------------------------------
typedef struct {
    VEHICLE_IGNITION_t          ingition;
    VEHICLE_COUNTRY_t           country;
    vehicle_date_t              date;
    vehicle_time_t              time;
    VEHICLE_DISPLAY_MODE_t      display_mode;
    vehicle_position_t          position;
} __attribute__ ((__packed__))  vehicle_system_t;


// -----------------------------------------------------------------------------
// Dynamic
// -----------------------------------------------------------------------------
typedef enum {
    VEHICLE_TURN_MODE_OFF       = 0,
    VEHICLE_TURN_MODE_RIGHT     = 1,
    VEHICLE_TURN_MODE_LEFT      = 2,
    VEHICLE_TURN_MODE_PARKING   = 3,
} __attribute__ ((__packed__))  VEHICLE_TURN_MODE_t;

typedef enum {
    VEHICLE_TURN_BLINK_OFF      = 0,
    VEHICLE_TURN_BLINK_ON       = 1,
} __attribute__ ((__packed__))  VEHICLE_TURN_BLINK_t;

typedef struct {
    VEHICLE_TURN_MODE_t         mode        : 2;
    VEHICLE_TURN_BLINK_t        blink       : 2;
    uchar                       r0          : 4;
} __attribute__ ((__packed__))  vehicle_turn_t;

typedef enum {
    VEHICLE_GEAR_MODE_STOP      = 0,                    //Park/Neutral
    VEHICLE_GEAR_MODE_FORWARD   = 1,                    //Drive/Low...
    VEHICLE_GEAR_MODE_REVERSE   = 2,
} __attribute__ ((__packed__))  VEHICLE_GEAR_MODE_t;

typedef struct {
    VEHICLE_GEAR_MODE_t         mode;
    char                        text;                   // ASCII (0~9, A~Z)
                                                        //  Manual
                                                        //    "123456NR"
                                                        //  Automatic
                                                        //    "PRNDL"
                                                        //     Park, Reverse, Neutral
                                                        //     Drive, Low
} __attribute__ ((__packed__))  vehicle_gear_t;

typedef struct {
    short                       g_accel;                // -512~512 (0.01G)
    short                       g_break;                // -512~512 (0.01G)
    short                       g_right;                // -512~512 (0.01G)
    short                       g_left;                 // -512~512 (0.01G)
} __attribute__ ((__packed__))  vehicle_gforce_t;


//------------------------------
typedef struct {
    uchar                       speed;                  // 0~255 (km/h)
    ushort                      tacho;                  // 0~65535 (rmp)
    uint                        odo;                    // 0~7FFFFFFF (km)
    ushort                      trip;                   // 0~65535 (km)
    ushort                      remain;                 // 0~65535 (km)
    vehicle_turn_t              turn;
    vehicle_gear_t              gear;
    char                        drive_mode[12];         // ASCII STRING
                                                        //  "Normal"
                                                        //  "Eco"
                                                        //  "Power"
                                                        //  "Sport"
                                                        //  "Comfortable"
                                                        //  "City"
                                                        //  …
    short                       lean_angle;             // -180~180 (degree)
    vehicle_gforce_t            gforce;
} __attribute__ ((__packed__))  vehicle_dynamic_t;


// -----------------------------------------------------------------------------
// Battery
// -----------------------------------------------------------------------------
typedef enum {
    CHARGER_MODE_IDLE           = 0,
    CHARGER_MODE_CHARGE_FAST    = 1,
    CHARGER_MODE_CHARGE_NORMAL  = 2,
    CHARGER_MODE_DISCHARGE      = 3,
} __attribute__ ((__packed__))  CHARGER_MODE_t;


//------------------------------
typedef struct {
    ushort                      voltage;        // 0~3600 (0.01v)
    ushort                      capacity;       // 0~1200 (0.1Ah)
    char                        temperature;    // -40~80 (C)
    CHARGER_MODE_t              charger;
} __attribute__ ((__packed__))  vehicle_battery_t;


// -----------------------------------------------------------------------------
// Sensor
// -----------------------------------------------------------------------------
typedef char                    FUEL_t;
typedef char                    AMBIENT_LIGHT_t;
typedef char                    AMBIENT_TEMPERATURE_t;
typedef char                    WATER_TEMPERATURE_t;
typedef char                    OIL_TEMPERATURE_t;          // -127~127 (C)


//------------------------------
typedef struct {
    char                        fuel;                       // 0~100 (%)
    uchar                       ambient_light;              // 0~255
    char                        ambient_temperature;        // -127~127 (C)
    char                        water_temperature;          // -127~127 (C)
    char                        oil_temperature;            // -127~127 (C)
} __attribute__ ((__packed__))  vehicle_sensor_t;

// -----------------------------------------------------------------------------
// Symbol0
typedef enum {
    VEHICLE_HEAD_LIGHT_OFF      = 0,
    VEHICLE_HEAD_LIGHT_REGULAR  = 1,
    VEHICLE_HEAD_LIGHT_BRIGHTS  = 2,
} __attribute__ ((__packed__))  VEHICLE_HEAD_LIGHT_t;


typedef struct {
    VEHICLE_HEAD_LIGHT_t        head_light      : 2;
    uchar                       fog_light       : 1;
    uchar                       oil             : 1;
    uchar                       fuel            : 1;
    uchar                       engine          : 1;
    uchar                       battery         : 1;
    uchar                       r0              : 1;
} __attribute__ ((__packed__))  vehicle_symbol0_t;


// -----------------------------------------------------------------------------
// Vehicle
typedef struct
{
    vehicle_system_t            system;
    vehicle_dynamic_t           dynamic;
    vehicle_battery_t           battery;
    vehicle_sensor_t            sensor;
    vehicle_symbol0_t           symbol0;
} __attribute__ ((__packed__))  vehicle_t;

int vehicle_parser(char *d, size_t l, vehicle_t *t);

#endif // __VEHICLE_H__

#ifdef __cplusplus
}
#endif
