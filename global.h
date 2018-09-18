#ifdef __cplusplus
extern "C" {
#endif

#ifndef __GLOBAL_H__
#define __GLOBAL_H__
/******************************************************************************
 * file         global.h
 * name         xzhong
 * 2017.09.15   PROTOCOL_GRP_t
 *              0x00~0x3F: basic, device ...
 *              0x40~    : function, features ...
 * 2017.07.21   rev HDR(1byte) to GRP(1byte)+HDR(1byte)
 * 2017.07.20   add SYSTEM_ID_LANGUAGE
 *              rem PROTOCOL_ID_HMI_ROTARY
 * 2017.07.18   Fisrt Release
 *****************************************************************************/

/******************************************************************************
 * LittleEndian vs. BigEndian
 *
 * BTYES = 0x12345678
 *    ---------------------------------------
 *    LittleEndian            BigEndian
 *    ---------------------------------------
 *    B0   B1  B2  B3         B0   B1  B2  B3
 *    78   56  34  12         12   34  56  78
 *    ----------------------------------------
 *
 * BITS
 *    struct {               struct {
 *       char b0 : 1;            char b7 : 1;
 *       char b1 : 1;            char b6 : 1;
 *       char b2 : 1;            char b5 : 1;
 *       char b3 : 1;            char b4 : 1;
 *       char b4 : 1;            char b3 : 1;
 *       char b5 : 1;            char b2 : 1;
 *       char b6 : 1;            char b1 : 1;
 *       char b7 : 1;            char b0 : 1;
 *    } LE;                  } BE;
 *
 * STRUCT
 *    struct {
 *       char  B0;
 *       char  B1;
 *
 *       typedef union {
 *          short S0;
 *          char  B3B4[2];
 *       } S0_t;
 *
 *    } LEBE_MIX;
 *
 *    B0 = 0x12
 *    B1 = 0x34
 *    S0 = 0x5678;
 *
 *    ---------------------------------------
 *    LittleEndian            BigEndian
 *    ---------------------------------------
 *    B0   B1  B2  B3         B0   B1  B2  B3
 *    12   34  78  56         12   34  56  78
 *    ----------------------------------------
 *
 ******************************************************************************/
//
#define B00         0x00
#define B01         0x01
#define B10         0x02
#define B11         0x03

#define B0000       0x00
#define B0001       0x01
#define B0010       0x02
#define B0011       0x03
#define B0100       0x04
#define B0101       0x05
#define B0110       0x06
#define B0111       0x07
#define B1000       0x08
#define B1001       0x09
#define B1010       0x0A
#define B1011       0x0B
#define B1100       0x0C
#define B1101       0x0D
#define B1110       0x0E
#define B1111       0x0F

#define B00000000   0x00
#define B00000001   0x01
#define B00000010   0x02
#define B00000100   0x04
#define B00001000   0x08
#define B00010000   0x10
#define B00100000   0x20
#define B01000000   0x40
#define B10000000   0x80

// -----------------------------------------------------------------------------
//
#define OS_LINUX    1

#if OS_LINUX
#include <sys/types.h>
typedef unsigned char       uchar;
#else
typedef unsigned char       uchar;
typedef unsigned long int   ulong;
typedef unsigned short int  ushort;
typedef unsigned int        uint;
#endif

// -----------------------------------------------------------------------------
//
typedef ssize_t (*sender_t)(const void *d, size_t l);


// -----------------------------------------------------------------------------
// Misc
#define STRNCMP(a,b)        strncmp(a, b, strlen(b))
#define IDC                 0                           //I Don't Care


//The use of ASCII 31 Unit separator as a field separator and ASCII 30 Record separator
//solves the problem of both field and record delimiters that appear in a text data stream.[18]
//
#define ACRS                 '\x1E'     //ASCII Charactor Record Separator
#define ASRS                 "\x1E"     //ASCII String    Record Separator
#define ACUS                 '\x1F'     //ASCII Charactor Unit   Separator
#define ASUS                 "\x1F"     //ASCII String    Unit   Separator

// -----------------------------------------------------------------------------
// Enum
typedef enum
{
    EON_OFF,
    EON_ON,
    EON_OFFING,
    EON_ONING,
} __attribute__ ((__packed__)) EON_t;

typedef enum
{
    PROTOCOL_TYPE_ACK,
    PROTOCOL_TYPE_CAN,
    PROTOCOL_TYPE_GPS,
    PROTOCOL_TYPE_MCU,
    PROTOCOL_TYPE_AVMT,
    PROTOCOL_TYPE_IPC
} __attribute__ ((__packed__)) PROTOCOL_TYPE_t;

typedef enum
{
    PROTOCOL_GRP_SYSTEM                 = 0x00,
    PROTOCOL_GRP_HMI                    = 0x01,
    PROTOCOL_GRP_AUDIO                  = 0x02,
    PROTOCOL_GRP_VIDEO                  = 0x03,
    PROTOCOL_GRP_VEHICLE                = 0x04,
    PROTOCOL_GRP_UPGRADE                = 0x05,
    PROTOCOL_GRP_GPS                    = 0x06,
    PROTOCOL_GRP_WIFI                   = 0x07,
    PROTOCOL_GRP_BLUETOOTH              = 0x08,
    PROTOCOL_GRP_DVR                    = 0x09,

    PROTOCOL_GRP_SNAVI                  = 0x40,
    PROTOCOL_GRP_WEATHER                = 0x41,
    PROTOCOL_GRP_MESSAGER               = 0x42,
    PROTOCOL_GRP_LIVE                   = 0x43,

} PROTOCOL_GRP_t;

#endif // __GLOBAL_H__

#ifdef __cplusplus
}
#endif
