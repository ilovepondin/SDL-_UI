#ifdef __cplusplus
extern "C" {
#endif

#ifndef __VEHICLE_H__
#define __VEHICLE_H__
/******************************************************************************
 * file         vehicle.h
 * name         xzhong
 * 2017.08.01   add vehicle_tracker_gps_t
 * 2017.07.21   mov VEHICLE_ID_t from global.h to vehicle.h
 * 2017.07.20   rev acceleration range 0~10 > 0~18
 *              rev drive_mode "0" from None to Normal
 *              add battery chager mode
 *              add malfunc code, error code
 * 2017.07.18   fisrt release
 *****************************************************************************/
#include <stdint.h>
#include "global.h"

typedef enum
{
    VEHICLE_ID_IGNITION         = 0x00,
    VEHICLE_ID_LIGHT            = 0x01,
    VEHICLE_ID_ENGINE           = 0x02,
    VEHICLE_ID_MILEAGE          = 0x03,
    VEHICLE_ID_CONTROL          = 0x04,
    VEHICLE_ID_BATTERY          = 0x05,
    VEHICLE_ID_MALFUNC_CODE     = 0x06,
    VEHICLE_ID_ERROR_CODE       = 0x07,
    VEHICLE_ID_TRACKER_GPS      = 0x08,
    VEHICLE_ID_MAX
} __attribute__ ((__packed__))  VEHICLE_ID_t;

// -----------------------------------------------------------------------------
// Ignition
typedef enum {
    IGNITION_LOCK               = 0,
    IGNITION_OFF                = 1,
    IGNITION_ACC                = 3,
    IGNITION_ON                 = 4,
    IGNITION_START              = 5,
} __attribute__ ((__packed__))  IGNITION_t;

//------------------------------
typedef struct {
    IGNITION_t                  state           : 4;
    uchar                       r0              : 4;
} __attribute__ ((__packed__))  vehicle_ingition_t;

// -----------------------------------------------------------------------------
// Light
typedef uchar                   LIGHT_SENSOR_t; // 0~255

typedef enum {
    HEAD_LIGHT_OFF              = 0,
    HEAD_LIGHT_REGULAR          = 1,
    HEAD_LIGHT_BRIGHTS          = 2,
} __attribute__ ((__packed__))  HEAD_LIGHT_t;

typedef enum {
    FOG_LIGHT_OFF               = 0,
    FOG_LIGHT_ON                = 1,
} __attribute__ ((__packed__))  FOG_LIGHT_t;

typedef enum {
    SIGNAL_LIGHT_OFF            = 0b00,
    SIGNAL_LIGHT_RIGHT          = 0b01,
    SIGNAL_LIGHT_LEFT           = 0b10,
    SIGNAL_LIGHT_WARINING       = 0b11,
} __attribute__ ((__packed__))  SIGNAL_LIGHT_t;

//------------------------------
typedef struct {
    LIGHT_SENSOR_t              light_sensor    : 8;
    HEAD_LIGHT_t                head_light      : 2;
    FOG_LIGHT_t                 fog_light       : 2;
    SIGNAL_LIGHT_t              signal_light    : 2;
    uchar                       r0              : 2;
} __attribute__ ((__packed__))  vehicle_light_t;

// -----------------------------------------------------------------------------
// Engine
typedef uchar                   SPEED_t;        // 0~255 (km/h)
typedef ushort                  TACHO_t;        // 轉速 0~65535 (rmp)
typedef uchar                   ACCELERATION_t; // 0~18 (level)

//------------------------------
typedef struct {
    SPEED_t                     speed;
    TACHO_t                     tacho;
    ACCELERATION_t              acceleration;
} __attribute__ ((__packed__))  vehicle_engine_t;

// -----------------------------------------------------------------------------
// Mileage
typedef int                     ODO_t;          // 0~7FFFFFFF (km)
typedef ushort                  TRIP_t;         // 0~65535 (km)
typedef ushort                  REMAIN_t;       // 0~65535 (km)

//------------------------------
typedef struct {
    ODO_t                       odo;            //0~7FFFFFFF (km)
    TRIP_t                      trip;           //0~65535 (km)
    REMAIN_t                    remain;         //0~65535 (km)
} __attribute__ ((__packed__))  vehicle_mileage_t;

// -----------------------------------------------------------------------------
// Control
typedef enum {
    GEAR_AT_PARK                = 0,
    GEAR_AT_REVERSE             = 1,
    GEAR_AT_NEUTRAL             = 2,
    GEAR_AT_DRIVE               = 3,
    GEAR_AT_LOW                 = 4
} __attribute__ ((__packed__))  GEAR_AT_t;

typedef enum {
    GEAR_MT_N                   = 0,
    GEAR_MT_1                   = 1,
    GEAR_MT_2                   = 2,
    GEAR_MT_3                   = 3,
    GEAR_MT_4                   = 4,
    GEAR_MT_5                   = 5,
    GEAR_MT_R                   = 6,
} __attribute__ ((__packed__))  GEAR_MT_t;

typedef uchar                   GEAR_t;

typedef enum {
    REVERSE_OFF                 = 0,
    REVERSE_ON                  = 1,
} __attribute__ ((__packed__))  REVERSE_t;

typedef enum {
    TRANSMISSION_MT             = 0,
    TRANSMISSION_AT             = 1,
} __attribute__ ((__packed__))  TRANSMISSION_t;

typedef enum {
    DRIVING_MODE_NORMAL         = 0,
    DRIVING_MODE_ECO            = 1,
    DRIVING_MODE_POWER          = 2,
    DRIVING_MODE_SPORT          = 3,
} __attribute__ ((__packed__))  DRIVING_MODE_t;

//------------------------------
typedef struct {
    GEAR_t                      gear                : 3;       //GEAR_AT_t GEAR_MT_t
    REVERSE_t                   reverse             : 1;
    uchar                       r0                  : 3;
    TRANSMISSION_t              transmission        : 1;

    DRIVING_MODE_t              drive_mode;
} __attribute__ ((__packed__))  vehicle_control_t;

// -----------------------------------------------------------------------------
// Battery
typedef enum {
    CHARGER_MODE_IDLE           = 0,
    CHARGER_MODE_CHARGE_FAST    = 1,
    CHARGER_MODE_CHARGE_NORMAL  = 2,
    CHARGER_MODE_DISCHARGE      = 3,
} __attribute__ ((__packed__))  CHARGER_MODE_t;

typedef struct {
    ushort                      voltage;                // 0~3600 (0.01v)
    ushort                      capacity;               // 0~1200 (0.1Ah)
    char                        temperature;            // -40~80 (C)
    CHARGER_MODE_t              charger_mode;
} __attribute__ ((__packed__))  vehicle_battery_t;

// -----------------------------------------------------------------------------
// Malfunc Code
typedef struct {
    ushort                      code;
} __attribute__ ((__packed__))  vehicle_malfunc_code_t;

// -----------------------------------------------------------------------------
// Error Code
typedef struct {
    ushort                      code;
} __attribute__ ((__packed__))  vehicle_error_code_t;

// -----------------------------------------------------------------------------
// Tracker GPS
typedef struct {
    int32_t                     latitude;               //range -180000000 ~ +180000000
                                                        //unit  0.000001°
                                                        //ex    123123456=123.123456°
    int32_t                     longitude;              //range -180000000 ~ +180000000
                                                        //unit  0.000001°
                                                        //ex    123123456=123.123456°
} __attribute__ ((__packed__))  vehicle_tracker_gps_t;

// -----------------------------------------------------------------------------
// Vehicle
typedef struct
{
    vehicle_ingition_t          ingition;
    vehicle_light_t             light;
    vehicle_engine_t            engine;
    vehicle_mileage_t           mileage;
    vehicle_control_t           control;
    vehicle_battery_t           battery;
    vehicle_malfunc_code_t      malfunc_code;
    vehicle_error_code_t        error_code;
    vehicle_tracker_gps_t       tracker_gps;
} __attribute__ ((__packed__))  vehicle_t;


// -----------------------------------------------------------------------------
// API
ssize_t vehicle_cmd(sender_t sender, VEHICLE_ID_t id, char *d, size_t l);
ssize_t vehicle_msg(sender_t sender, VEHICLE_ID_t id, char *d, size_t l);

#endif // __VEHICLE_H__

#ifdef __cplusplus
}
#endif
