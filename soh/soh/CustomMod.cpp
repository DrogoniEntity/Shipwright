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

extern PlayState* gPlayState;

static void CustomMod_UpdatePlayerScale();

void CustomMod_RegisterCustomScaleMod()
{
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneInit>([](uint32_t sceneNum) {
       CustomMod_UpdatePlayerScale();
    });
}

void CustomMod_DrawCustomMenu()
{
    if (ImGui::BeginMenu("Custom"))
    {
        if (UIWidgets::EnhancementSliderFloat("Player Scale", "##PlayerScale", CUSTOMMOD_CUSTOM_SCALE_KEY, 0.3f, 4.0f, "%f", 1.0f, false))
        {
            CustomMod_UpdatePlayerScale();
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            CVarClear(CUSTOMMOD_CUSTOM_SCALE_KEY);
            CustomMod_UpdatePlayerScale();
        }

        ImGui::EndMenu();
    }
}

static void CustomMod_UpdatePlayerScale()
{
    if (gPlayState == nullptr)
        return;

    float scale = CVarGetFloat(CUSTOMMOD_CUSTOM_SCALE_KEY, 1.0f) / 100.0f;
    Player* player = GET_PLAYER(gPlayState);

    player->actor.scale.x = scale;
    player->actor.scale.y = scale;
    player->actor.scale.z = scale;
}