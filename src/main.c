#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "primitive/primitive.h"
#include "bvh/bvh.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "lidar/lidar.h"
#include "rlgl.h"

void DrawSmallPoint3D(Vector3 position, Color color)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlBegin(RL_LINES);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlVertex3f(0.0f, 0.0f, 0.0f);
    rlVertex3f(0.0f, 0.0f, 0.01f);
    rlEnd();
    rlPopMatrix();
}

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "3D BVH");

    DisableCursor();

    SetTargetFPS(60);

    Camera *camera = create_camera();
    Primitive *primitives = create_scene();
    BVH_Tree *tree = build_bvh_tree(primitives, PRIMITIVE_COUNT, SCENE_BOUNDING_BOX);

    Vector3 *collisions = malloc(sizeof(Vector3) * 50000);
    size_t *collision_count = malloc(sizeof(size_t));
    *collision_count = 0;

    bool draw_bvh = true;

    bool *animating_lidar = malloc(sizeof(bool));
    *animating_lidar = false;

    while (!WindowShouldClose())
    {

        // Clear collisions
        if (!*animating_lidar && IsKeyPressed(KEY_F))
        {
            *collision_count = 0;
        }

        // Reveal BVH tree
        if (IsKeyPressed(KEY_T))
        {
            draw_bvh = !draw_bvh;
        }

        // Shoot rays from camera
        if (!*animating_lidar && IsKeyPressed(KEY_R))
        {
            *animating_lidar = true;
            lidar_animation(tree, camera, collisions, collision_count, animating_lidar);
        }

        update_camera(camera);

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(*camera);

        // Draw all collisions
        for (size_t i = 0; i < *collision_count; i++)
        {
            DrawSmallPoint3D(collisions[i], WHITE);
        }

        // Draw the bounding volumes
        if (draw_bvh)
        {
            draw_bvh_tree(tree);
        }

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    free(primitives);
    free(collisions);
    free(animating_lidar);
    free_bvh_tree(tree);
    free(camera);
    free(collision_count);

    return 0;
}