#ifndef __CUSTOM_MOD_H__
#define __CUSTOM_MOD_H__

#include <libultraship/bridge.h>

/**
 * \file CustomMod.h
 * \brief Custom mod definitions.
 * 
 * It contains all definitions and functions about custom mod of this build.
 */

#ifdef __cplusplus
extern "C"
{
    #include <stdbool.h>
#endif

//////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////

/**
 * Configuration key for "Custom Player Scale".
 */
#define CUSTOMMOD_CUSTOM_SCALE "custom.scale"

/**
 * Configuration key for "Random scale".
 */
#define CUSTOMMOD_RANDOM_SCALE "custom.randomScale"

/**
 * Configuration key for "Hide equipments on back".
 */
#define CUSTOMMOD_HIDE_EQUIP_ON_BACK "custom.hideEquipOnBack"

/**
 * Configuration key for "Timeless tunics and boots".
 */
#define CUSTOMMOD_TIMELESS_TUNICS "custom.timelessTunics"

/**
 * Configuration key for "Sync tunics and boots".
 */
#define CUSTOMMOD_SYNC_TUNICS "custom.syncTunics"

/**
 * Configuration key "Show clock".
 */
#define CUSTOMMOD_CLOCK "custom.clock"

//////////////////////////////////////////////
// Mod installation
//////////////////////////////////////////////

/**
 * Render "Custom" menu in menu bar.
 */
void CustomMod_DrawCustomMenu();

/**
 * Register game hooks for "Random scale" mod.
 */
void CustomMod_RegisterRandomScaleHooks();

/**
 * Render custom overlays.
 */
void CustomMod_DrawOverlay();

//////////////////////////////////////////////
// Getters
//////////////////////////////////////////////

/**
 * Get "Custom Player Scale" value. Default value is `1.0`.
 * \return custom scale value
 */
inline float CustomMod_GetCustomScale()
{
    return CVarGetFloat(CUSTOMMOD_CUSTOM_SCALE, 1.0f);
}

/**
 * Get "Random Scale" flag statement.
 * \return `true` if mod is enabled
 */
inline bool CustomMod_IsRandomScale()
{
    return CVarGetInteger(CUSTOMMOD_RANDOM_SCALE, false);
}

/**
 * Get "Hide equipments on back" flag statement.
 * \return `true` if mod is enabled
 */
inline bool CustomMod_IsHideEquipOnBack()
{
    return CVarGetInteger(CUSTOMMOD_HIDE_EQUIP_ON_BACK, false);
}

/**
 * Get "Timeless tunics and boots" flag statement.
 * \return `true` if mod is enabled
 */
inline bool CustomMod_IsTimelessTunics()
{
    return CVarGetInteger(CUSTOMMOD_TIMELESS_TUNICS, false);
}

/**
 * Get "Sync tunics and boots" flag statement.
 * \return `true` if mod is enabled
 */
inline bool CustomMod_IsSyncTunics()
{
    return CVarGetInteger(CUSTOMMOD_SYNC_TUNICS, false);
}

/**
 * Get "Show clock" flag statement.
 * \return `true` if mod is enabled
 */
inline bool CustomMod_IsClock()
{
    return CVarGetInteger(CUSTOMMOD_CLOCK, false);
}

#ifdef __cplusplus
}
#endif
#endif