#ifndef __CUSTOM_MOD_H__
#define __CUSTOM_MOD_H__

#ifdef __cplusplus
extern "C" {
#endif

#define CUSTOMMOD_CUSTOM_SCALE_KEY "custom.scale"
#define CUSTOMMOD_HIDE_EQUIP_ON_BACK "custom.hideEquipOnBack"

void CustomMod_RegisterCustomScaleMod();
void CustomMod_DrawCustomMenu();

#ifdef __cplusplus
}
#endif
#endif