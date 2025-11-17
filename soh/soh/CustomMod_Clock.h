#ifndef __CUSTOM_MOD_CLOCK_H__
#define __CUSTOM_MOD_CLOCK_H__

/**
 * \file CustomMod_Clock.h
 * \brief Specialised C module for clock mod
 * 
 * It's necessary to externalize clock rendering into C module to
 * avoir compilation errors with C++ modules.
 */

#ifdef __cplusplus
extern "C"
{
#endif
#include <z64.h>

/**
 * Draw clock on GUI.
 * \param play PlayState's instance
 */
void CustomModClock_Draw(PlayState* play);

#ifdef __cplusplus
}
#endif
#endif