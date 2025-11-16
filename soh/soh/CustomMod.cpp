#include "CustomMod.h"

#include <libultraship/bridge.h>
#include "Enhancements/game-interactor/GameInteractor.h"

#include "ImGui/imgui.h"
#include "UIWidgets.hpp"

extern "C"
{
    #include <z64.h>
    #include "macros.h"
}

/**
 * Play statement.
 */
extern PlayState* gPlayState;

/**
 * Update player's actor scale with custom scale.
 */
static void CustomMod_UpdatePlayerScale();

void CustomMod_DrawCustomMenu()
{
    if (ImGui::BeginMenu("Custom"))
    {
        // Hide equipment on back
        UIWidgets::PaddedEnhancementCheckbox("Hide equipments on back", CUSTOMMOD_HIDE_EQUIP_ON_BACK, true, false);
        UIWidgets::Tooltip("Never display sword and shield on player's back even if sword or shield is equipped");

        // Timeless tunics and boots
        UIWidgets::PaddedEnhancementCheckbox("Timeless tunics and boots", CUSTOMMOD_TIMELESS_TUNICS, true, false);
        UIWidgets::Tooltip("Allow to equip any tunics and boots regardless to player's age");

        // Sync tunics and boots between ages
        UIWidgets::PaddedEnhancementCheckbox("Sync tunics and boots between age", CUSTOMMOD_SYNC_TUNICS);
        UIWidgets::Tooltip("Synchronize equiped tunics and boots between player's age. Work only of all player's age can equip it.");

        // Custom Scale
        if (UIWidgets::EnhancementSliderFloat("Custom Scale", "##PlayerScale", CUSTOMMOD_CUSTOM_SCALE, 0.3f, 4.0f, "%.2f", 1.0f, false))
        {
            CustomMod_UpdatePlayerScale();
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            CVarClear(CUSTOMMOD_CUSTOM_SCALE);
            CustomMod_UpdatePlayerScale();
        }

        // Random Scale
        UIWidgets::PaddedEnhancementCheckbox("Random Player Growth", CUSTOMMOD_RANDOM_SCALE, true, false);
        UIWidgets::Tooltip("Make player's scale to change dynamically while playing and loading new scene (change between 1.0 to 2.0)");

        ImGui::EndMenu();
    }
}

void CustomMod_RegisterRandomScaleHooks()
{
    static int frameToWait = 0;
    static float targetScale = 1.0f;
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>([]() {
        // Do nothing if play context or mod isn't enabled
        if (gPlayState == nullptr || !CustomMod_IsRandomScale())
            return;

        frameToWait--;
        if (frameToWait <= 0)
        {
            // Give more probability to keep normal scale than bigger scale
            if ((rand() % 3) == 0)
            {
                targetScale = 1.0f;
            }
            else
            {
                // Range : 1.1 <-> 2.0 (step = 0.1)
                int selection = rand() % /*((2.0 - 1.1) * 10) + 1*/10;
                targetScale = 1.1f + (((float) selection) / 10.0f);
            }

            frameToWait = rand() % 160 + 160;
        }

        // Progressively change player's scale between each update
        float newScale = CustomMod_GetCustomScale();
        if (newScale != targetScale)
        {
            if (newScale > (targetScale - 0.02) && newScale < (targetScale + 0.02))
                newScale = targetScale;
            else if (newScale < targetScale)
                newScale += 0.01;
            else
                newScale -= 0.01;
            CVarSetFloat(CUSTOMMOD_CUSTOM_SCALE, newScale);
            CustomMod_UpdatePlayerScale();
        }
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneInit>([](uint16_t sceneNum) {
        // Request to change scale on scene load
        frameToWait = 0;
    });
}

static void CustomMod_UpdatePlayerScale()
{
    if (gPlayState == nullptr)
        return;

    float scale = CustomMod_GetCustomScale() / 100.0f;
    Player* player = GET_PLAYER(gPlayState);

    player->actor.scale.x = scale;
    player->actor.scale.y = scale;
    player->actor.scale.z = scale;
}