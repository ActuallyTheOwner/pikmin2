#ifndef _DOLPHIN_RAND_H
#define _DOLPHIN_RAND_H

#include "types.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

#define RAND_MAX         (32768.0f)
#define RAND_EBISAWA_MAX (32767.0f)

inline f32 randEbisawaFloat() { return (f32)rand() / RAND_EBISAWA_MAX; }
inline f32 randFloat() { return (f32)rand() / RAND_MAX; }
inline f32 randWeightFloat(f32 range) { return (range * (f32)rand()) / RAND_MAX; }

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
