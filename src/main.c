#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "primitive/primitive.h"
#include "bvh/bvh.h"
#include "scene/scene.h"
#include "camera/camera.h"
#include "raymath.h"

#define DEG2RAD(deg) ((deg) * M_PI / 180.0)

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "3D BVH");

    DisableCursor();

    SetTargetFPS(60);

    Camera camera = create_camera();
    Primitive *primitives = create_scene();
    BVH_Tree *tree = build_bvh_tree(primitives, PRIMITIVE_COUNT, SCENE_BOUNDING_BOX);

    size_t ray_count = 100;
    Ray *rays = malloc(sizeof(Ray) * ray_count);

    Vector3 *collisions = malloc(sizeof(Vector3) * 3000);
    size_t collision_count = 0;

    bool draw_bvh = true;

    while (!WindowShouldClose())
    {

        Vector3 direction = Vector3Subtract(camera.target, camera.position); 
        direction = Vector3Normalize(direction);

        // Clear collisions
        if (IsKeyPressed(KEY_F))
        {
            collision_count = 0;
        }

        // Reveal BVH tree
        if (IsKeyPressed(KEY_T)) {
            draw_bvh = !draw_bvh;
        }

        // Shoot rays from camera
        if (IsKeyPressed(KEY_R))
        {
            // Shoot all of the rays in the direction of the camera but with horizontal offset
            for (size_t i = 0; i < ray_count; i++)
            {
                float offset = ((float)i / (float)ray_count - 0.5f) * camera.fovy;
                Matrix rotationMatrix = MatrixRotateY(DEG2RAD(offset));
                Vector3 ray_direction = Vector3Transform(direction, rotationMatrix);

                ray_direction = Vector3Normalize(ray_direction);

                rays[i] = (Ray){camera.position, ray_direction};

                Vector3 collision = check_bvh_collision_ray(tree, rays[i]);
                if (collision.x != 0 && collision.y != 0 && collision.z != 0)
                {
                    collisions[collision_count] = collision;
                    collision_count++;
                }
            }
        }

        update_camera(&camera);

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        // Draw all collisions
        for (size_t i = 0; i < collision_count; i++)
        {
            DrawSphere(collisions[i], 0.01, WHITE);
        }

        // Draw the bounding volumes
        if (draw_bvh) {
            draw_bvh_tree(tree);
        }

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    free(primitives);

    return 0;
}