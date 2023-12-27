#include <stdlib.h>
#include <stdio.h>
#include "consts.h"
#include "raylib.h"
#include "primitive/primitive.h"
#include "bvh/bvh.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "lidar/lidar.h"
#include "rlgl.h"

void update(volatile Vector3 *collisions, volatile size_t *collision_count, volatile bool *animating_lidar, bool draw_bvh, const BVH_Tree *tree, Camera *camera);
void draw(volatile Vector3 *collisions, volatile size_t *collision_count, bool draw_bvh, const BVH_Tree *tree, Camera *camera);
void DrawSmallPoint3D(Vector3 position, Color color);

int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D BVH");
    DisableCursor();
    SetTargetFPS(FPS);

    Camera *camera = camera_create();
    Primitive *scene = scene_create();
    BVH_Tree *tree = bvh_tree_create(scene, PRIMITIVE_COUNT, SCENE_BOUNDING_BOX);

    volatile Vector3 *collisions = malloc(sizeof(Vector3) * MAX_COLLISIONS);
    volatile size_t *collision_count = malloc(sizeof(size_t));

    bool draw_bvh = true;
    volatile bool *animating_lidar = malloc(sizeof(bool));
    *animating_lidar = false;

    while (!WindowShouldClose())
    {
        update(collisions, collision_count, animating_lidar, draw_bvh, tree, camera);
        draw(collisions, collision_count, draw_bvh, tree, camera);
    }

    CloseWindow();
    free(scene);
    free((void *)collisions);
    free((void *)animating_lidar);
    bvh_tree_free(tree);
    free((void *)camera);
    free((void *)collision_count);

    return 0;
}

void update(volatile Vector3 *collisions, volatile size_t *collision_count, volatile bool *animating_lidar, bool draw_bvh, const BVH_Tree *tree, Camera *camera)
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

    camera_update(camera);
}

void draw(volatile Vector3 *collisions, volatile size_t *collision_count, bool draw_bvh, const BVH_Tree *tree, Camera *camera)
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(*camera);

    // Draw all collisions
    for (size_t i = 0; i < *collision_count; i++)
    {
        DrawPoint3D(collisions[i], WHITE);
    }

    // Draw the bounding volumes
    if (draw_bvh)
    {
        draw_bvh_tree(tree);
    }

    EndMode3D();
    EndDrawing();
}

/// Draw a point in 3D space, actually a small line
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
