#include "CustomMod_Clock.h"

#include <z64.h>
#include "global.h"
#include "macros.h"

#include <time.h>

/**
 * Do clock printing on screen.
 * 
 * \param play current play state
 * \param gfx display list
 */
static void CustomModClock_PrintClock(PlayState* play, Gfx** gfx);

void CustomModClock_Draw(PlayState* play)
{
    Gfx* displayList;
    Gfx* prevDisplayList;

    OPEN_DISPS(play->state.gfxCtx);
    prevDisplayList = POLY_OPA_DISP;
    displayList = Graph_GfxPlusOne(POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, displayList);

    CustomModClock_PrintClock(play, &displayList);

    gSPEndDisplayList(displayList++);
    Graph_BranchDlist(prevDisplayList, displayList);
    POLY_OPA_DISP = displayList;
    CLOSE_DISPS(play->state.gfxCtx);
}

static void CustomModClock_PrintClock(PlayState* play, Gfx** gfx)
{
    static time_t last_timestamp = 0;
    static char time_sep = ' ';

    time_t current_timestamp = time(NULL);
    float time_elapsed = difftime(current_timestamp, last_timestamp);
    if (time_elapsed > 0.75f)
    {
        time_sep = time_sep == ' ' ? ':' : ' ';
        last_timestamp = time(NULL);
    }

    GfxPrint printer;
    s32 pad[2];

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, *gfx);

    int zeldaTimeHour = (u8) (24 * 60 / ((f32) 0x10000) * ((void)0, gSaveContext.dayTime) / 60.0f);
    int zeldaTimeMin = (s16) (24 * 60 / ((f32) 0x10000) * ((void)0, gSaveContext.dayTime)) % 60;
    struct tm* current_timeinfo = localtime(&current_timestamp);

    GfxPrint_SetPos(&printer, 1, 28);
    GfxPrint_SetColor(&printer, 255, 255, 55, 64);
    GfxPrint_Printf(&printer, "%s", "Zelda Time ");

    GfxPrint_SetColor(&printer, 255, 255, 255, 64);
    GfxPrint_Printf(&printer, "%02d%c%02d", zeldaTimeHour, time_sep, zeldaTimeMin);
    
    GfxPrint_SetColor(&printer, 55, 55, 255, 64);
    GfxPrint_SetPos(&printer, 20, 28);
    GfxPrint_Printf(&printer, "%s", "Console Time ");

    GfxPrint_SetColor(&printer, 255, 255, 255, 64);
    GfxPrint_Printf(&printer, "%02d%c%02d", current_timeinfo->tm_hour, time_sep, current_timeinfo->tm_min);

    *gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);
}