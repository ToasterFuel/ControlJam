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
#include "Graphics.h"
#include "Physics.h"
#include "Vector2.h"

static resolution_t res = RESOLUTION_640x480;
static bitdepth_t bit = DEPTH_32_BPP;

static float moveSpeed = 1;

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

    ComponentsList componentsList;

    /* These are pointers cause I'm doing a test. They don't need to be */
    Entity *player = (Entity *)malloc(sizeof(Entity));
    player->uuid = 0;
    ECS_AddComponentTransform(player->uuid, &componentsList, (Vector2){100, 100}, ZeroVector());
    ECS_AddComponentRectangleGraphic(player->uuid, &componentsList, 50, 50, 0xFF0000FF);
    ECS_AddComponentBoxCollider(player->uuid, &componentsList, ZeroVector(), 50, 50);
    ECS_AddComponentRigidBody(player->uuid, &componentsList, 1);

    Entity *obstacle = (Entity *)malloc(sizeof(Entity));
    obstacle->uuid = 1;
    ECS_AddComponentTransform(obstacle->uuid, &componentsList, (Vector2){200, 150}, ZeroVector());
    ECS_AddComponentRectangleGraphic(obstacle->uuid, &componentsList, 50, 50, 0x0000FFFF);
    ECS_AddComponentBoxCollider(obstacle->uuid, &componentsList, ZeroVector(), 50, 50);

    /* Use this shizz if you wanna see a bunch of blocks */

    //time_t t;
    //srand((unsigned) time(&t));
    for (int i = 0; i < 100; i++) {
        Entity x;
        x.uuid = 2 + i;
        ECS_AddComponentTransform(x.uuid, &componentsList, (Vector2){(float)(rand() % 400), (float)(rand() % 400)}, ZeroVector());
        int size = rand() % 50;
        ECS_AddComponentRectangleGraphic(x.uuid, &componentsList, size, size, 0x00FF00FF);
    }
    
    /**/

    int frame = 0;

    /* Main loop test */
    while (1)
    {
        frame++;
        static display_context_t disp = 0;

        /* Grab a render buffer */
        while (!(disp = display_lock()));

        /* Fill the screen */
        graphics_fill_screen(disp, 0x0);

        /* Set the text output color */
        graphics_set_color(0xFFFFFFFF, 0x0);

        /* Stupid stuff for testing */
        /*if (obstacle != NULL && BoxCollider_IsColliding(componentsList.transformComponents,
                                                        componentsList.boxColliderComponents.find(player->uuid)->second,
                                                        player->uuid,
                                                        componentsList.boxColliderComponents.find(obstacle->uuid)->second,
                                                        obstacle->uuid))
        {
            ECS_FreeEntity(obstacle, &componentsList);
        }*/

        /* To do initialize routines */
        controller_scan();

        /* Move the player */
        struct controller_data keys = get_keys_pressed();
        RigidBody_AddForce(componentsList.rigidBodyComponents[player->uuid], (Vector2){keys.c[0].x * moveSpeed, -keys.c[0].y * moveSpeed}, false);

        float time = 1.0 / 30.0;
        ECS_UpdateComponents(&componentsList, time);
        ECS_DrawComponents(&componentsList, disp);

        std::string frameCount = "Frames: " + std::to_string(frame);
        graphics_draw_text(disp, 20, 20, frameCount.c_str());

        /* PrintControllerStats(); */
        /* printf("Is it null? %s\n", (testSprite == NULL) ? "YES": "NO"); */

        /* Force backbuffer flip */
        display_show(disp);

        continue;
    }
}
