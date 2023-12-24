#include <stdlib.h>
#include "raylib.h"
#include "renderable/renderable.h"
#include "bvh/bvh.h"
#include "scene/scene.h"
#include "camera/camera.h"

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "3D BVH");

    DisableCursor();

    SetTargetFPS(60);

    Camera camera = create_camera();
    Renderable *renderables = create_scene();
    BVH_Tree *tree = build_bvh_tree(renderables, RENDERABLE_COUNT, SCENE_AABB);

    while (!WindowShouldClose())
    {
        update_camera(&camera);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // DrawGrid(1000, 1.0f);
        draw_bvh_tree(tree);

        draw_scene(renderables);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    free(renderables);

    return 0;
}