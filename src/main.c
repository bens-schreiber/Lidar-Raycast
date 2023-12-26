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

Camera *camera;
Primitive *primitives;
BVH_Tree *tree;

Vector3 *collisions;
size_t *collision_count;

bool draw_bvh;
bool *animating_lidar;

void update(void);
void draw(void);
void DrawSmallPoint3D(Vector3 position, Color color);

int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D BVH");
    DisableCursor();
    SetTargetFPS(FPS);

    camera = camera_create();
    primitives = scene_create();
    tree = bvh_tree_create(primitives, PRIMITIVE_COUNT, SCENE_BOUNDING_BOX);

    collisions = malloc(sizeof(Vector3) * MAX_COLLISIONS);
    collision_count = malloc(sizeof(size_t));
    *collision_count = 0;

    draw_bvh = true;

    animating_lidar = malloc(sizeof(bool));
    *animating_lidar = false;

    while (!WindowShouldClose())
    {
        update();
        draw();
    }

    CloseWindow();
    free(primitives);
    free(collisions);
    free(animating_lidar);
    bvh_tree_free(tree);
    free(camera);
    free(collision_count);

    return 0;
}

void update(void)
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

void draw(void)
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
