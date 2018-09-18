#ifdef __cplusplus
extern "C" {
#endif

#define __VEHICLE_VER__     1

#if (__VEHICLE_VER__ == 0)
#include "vehicle_v0.h"
#elif (__VEHICLE_VER__ == 1)
#include "vehicle_v1.h"
#else
#include "vehicle_v0.h"
#endif

#ifdef __cplusplus
}
#endif
