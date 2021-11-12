#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <libdragon.h>
#include <stdbool.h>
#include <string>

#include "ControllerTesting.h"
#include "ECS.h"
#include "Globals.h"
#include "Graphics.h"
#include "Physics.h"
#include "Vector2.h"

static resolution_t res = RESOLUTION_640x480;
static bitdepth_t bit = DEPTH_32_BPP;

static float moveSpeed = 1;

ComponentsList componentsList;

int main(void)
{
    /* enable interrupts (on the CPU) */
    init_interrupts();

    /* Initialize peripherals */
    display_init(res, bit, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    dfs_init(DFS_DEFAULT_LOCATION);
    controller_init();
    timer_init();
    rtc_init();

    console_set_render_mode(RENDER_MANUAL);
    sprite_t *testSprite = NULL;
    int fp = dfs_open("/TestSprite.sprite");
    if (fp > 0)
    {
        testSprite = (sprite_t *)malloc(dfs_size(fp));
        dfs_read(testSprite, 1, dfs_size(fp), fp);
        dfs_close(fp);
    }

    /* These are pointers cause I'm doing a test. They don't need to be */
    Entity *player = (Entity *)malloc(sizeof(Entity));
    player->uuid = 0;
    ECS_AddComponentTransform(player->uuid, (Vector2){100, 100}, ZeroVector());
    ECS_AddComponentRectangleGraphic(player->uuid, 50, 50, 0xFF0000FF);
    ECS_AddComponentBoxCollider(player->uuid, ZeroVector(), 50, 50);
    ECS_AddComponentRigidBody(player->uuid, 1);

    /* Use this shizz if you wanna see a bunch of blocks */

    time_t t;
    srand((unsigned)time(&t));
    int lastUUID = 0;


    for (int i = 0; i < 10; i++)
    {
        ++lastUUID;
        int uuid = lastUUID + i;
        int size = rand() % 50;
        ECS_AddComponentTransform(uuid, (Vector2){(float)(rand() % 400), (float)(rand() % 400)}, ZeroVector());
        ECS_AddComponentRectangleGraphic(uuid, size, size, (uint32_t)(rand() % 0xFFFFFFFF));
        ECS_AddComponentBoxCollider(uuid, ZeroVector(), size, size);
    }

    /**/

    int frame = 0;

    /* Main loop test */
    while (1)
    {
        frame++;
        static display_context_t disp = 0;

        /* Grab a render buffer */
        while (!(disp = display_lock()))
            ;

        /* Fill the screen */
        graphics_fill_screen(disp, 0x0);

        /* Set the text output color */
        graphics_set_color(0xFFFFFFFF, 0x0);

        /* Stupid stuff for testing */
        std::unordered_map<size_t, BoxCollider *>::iterator it = componentsList.boxColliderComponents.begin();
        while (it != componentsList.boxColliderComponents.end())
        {
            if (it->first != player->uuid &&
                BoxCollider_IsColliding(componentsList.boxColliderComponents.at(player->uuid),
                                        player->uuid,
                                        it->second,
                                        it->first))
            {
                size_t uuid = it->first;
                ++it;
                ECS_FreeByUUID(uuid);
            }
            else
            {
                ++it;
            }
        }
        for (std::unordered_map<size_t, BoxCollider *>::iterator it = componentsList.boxColliderComponents.begin();
            it != componentsList.boxColliderComponents.end();
            it++)
        {
            if (it->first != player->uuid &&
                BoxCollider_IsColliding(componentsList.boxColliderComponents.find(player->uuid)->second,
                                        player->uuid,
                                        it->second,
                                        it->first))
            {
                ECS_FreeByUUID(it->first);
            }
        }

        /* To do initialize routines */
        controller_scan();

        /* Move the player */
        struct controller_data keys = get_keys_pressed();
        RigidBody_AddForce(componentsList.rigidBodyComponents.at(player->uuid), (Vector2){keys.c[0].x * moveSpeed, -keys.c[0].y * moveSpeed}, false);

        float time = 1.0 / 10.0;
        ECS_UpdateComponents(time);
        ECS_DrawComponents(disp);

        std::string frameCount = "Frames: " + std::to_string(frame);
        graphics_draw_text(disp, 20, 20, frameCount.c_str());

        /* PrintControllerStats(); */
        /* printf("Is it null? %s\n", (testSprite == NULL) ? "YES": "NO"); */

        /* Force backbuffer flip */
        display_show(disp);

        continue;
    }
}
