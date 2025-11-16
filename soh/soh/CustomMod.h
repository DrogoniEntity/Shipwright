#ifndef __CUSTOM_MOD_H__
#define __CUSTOM_MOD_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CUSTOMMOD_CUSTOM_SCALE "custom.scale"
#define CUSTOMMOD_RANDOM_SCALE "custom.randomScale"

#define CUSTOMMOD_HIDE_EQUIP_ON_BACK "custom.hideEquipOnBack"
#define CUSTOMMOD_TIMELESS_TUNICS "custom.timelessTunics"
#define CUSTOMMOD_SYNC_TUNICS "custom.syncTunics"

void CustomMod_DrawCustomMenu();

void CustomMod_RegisterRandomScaleHooks();

#ifdef __cplusplus
}
#endif
#endif