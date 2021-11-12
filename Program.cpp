#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <libdragon.h>
#include <stdbool.h>
#include <string>
#include <vector>

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
    // Enable interrupts (on the CPU)
    init_interrupts();

    // Initialize peripherals
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

    Entity player;
    player.uuid = 0;
    ECS_AddEntity(player);
    ECS_AddComponentTransform(player.uuid, (Vector2){100, 100}, ZeroVector());
    ECS_AddComponentRectangleGraphic(player.uuid, 50, 50, 0xFFFFFFFF);
    ECS_AddComponentBoxCollider(player.uuid, ZeroVector(), 50, 50);
    ECS_AddComponentRigidBody(player.uuid, 1);


    time_t t;
    srand((unsigned)time(&t));

    int lastUUID = 0;

    for (int i = 0; i < 10; i++)
    {
        Entity e;
        lastUUID++;
        int uuid = lastUUID;
        e.uuid = uuid;
        int size = 10 + rand() % 40;
        ECS_AddEntity(e);
        ECS_AddComponentTransform(uuid, (Vector2){(float)(rand() % (SCREEN_X - size)), (float)(rand() % (SCREEN_Y - size))}, ZeroVector());
        ECS_AddComponentRectangleGraphic(uuid, size, size, (uint32_t)(rand() % 0xFFFFFFFF));
        ECS_AddComponentBoxCollider(uuid, ZeroVector(), size, size);
    }

    // This is really dumb and idk why we need it, but there's an error if we don't add a stupid, empty entity at the end. Which will be a problem later...
    Entity dumbShit;
    ECS_AddEntity(dumbShit);

    int frame = 0;

    // Main loop test
    while (1)
    {
        int entitiesCount = componentsList.entities.size();
        frame++;
        static display_context_t disp = 0;

        // Grab a render buffer
        while (!(disp = display_lock()));

        // Fill the screen
        graphics_fill_screen(disp, 0x0);

        // Set the text output color
        graphics_set_color(0xFFFFFFFF, 0x0);

        // Collide and destroy
        std::vector<Entity>::iterator it = componentsList.entities.begin();
        while (it != componentsList.entities.end())
        {
            if ((*it).uuid != player.uuid &&
                (*it).mask.test(4) &&
                componentsList.boxColliderComponents.count((*it).uuid) &&
                BoxCollider_IsColliding(componentsList.boxColliderComponents.at(player.uuid),
                                        player.uuid,
                                        componentsList.boxColliderComponents.at((*it).uuid),
                                        (*it).uuid))
            {
                size_t uuid = (*it).uuid;
                it++;
                ECS_FreeByUUID(uuid);
            }
            else {
                it++;
            }
        }

        // To do initialize routines
        controller_scan();

        // Move the player
        struct controller_data keys = get_keys_pressed();
        RigidBody_AddForce(componentsList.rigidBodyComponents.at(player.uuid), (Vector2){keys.c[0].x * moveSpeed, -keys.c[0].y * moveSpeed}, false);
        

        
        float time = 1.0 / 10.0;
        ECS_UpdateComponents(time);
        ECS_DrawComponents(disp);
        

        std::string frameCount = "Frames: " + std::to_string(frame);
        graphics_draw_text(disp, 20, 20, frameCount.c_str());
        std::string ents = "Entities: " + std::to_string(entitiesCount);
        graphics_draw_text(disp, 20, 0, ents.c_str());
        

        /* PrintControllerStats(); */
        /* printf("Is it null? %s\n", (testSprite == NULL) ? "YES": "NO"); */

        /* Force backbuffer flip */
        display_show(disp);

        continue;
    }
}
