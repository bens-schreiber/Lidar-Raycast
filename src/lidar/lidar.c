
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../consts.h"
#include "../primitive/primitive.h"
#include "../bvh/bvh.h"
#include "raymath.h"
#include "lidar.h"

/// @brief  Args for the lidar animation thread
typedef struct
{
    BVH_Tree *tree;
    Camera *camera;
    Vector3 *collisions;
    size_t *collision_count;
    bool *animating_lidar;
} LidarAnimationArgs;

/// The ray count within the bounds of the screen height.
#define MAX_VERTICAL Clamp(RAY_COUNT, 0, SCREEN_HEIGHT)

/// @brief Updates the collision count to stay within the bounds of the array, resetting to 0 on overflow
/// @param collision The current collision count
/// @return The updated collision count
#define update_collisions(collision) (collision + 1) % MAX_COLLISIONS

void animation_impl(BVH_Tree *tree, Camera *camera, Vector3 *collisions, size_t *collision_count)
{

    Vector3 direction, collision, ray_direction;
    float offset;
    Matrix rotationMatrix;
    Ray ray;

    // vertical offset of lidar
    for (float v = 0; v < MAX_VERTICAL; v++)
    {
        // Direction camera is looking in.
        // Recalculate after every thread sleep to account for camera movement
        direction = Vector3Subtract(camera->target, camera->position);
        direction = Vector3Normalize(direction);
        direction = Vector3Add(direction, (Vector3){0, 0 - direction.y + (v / RAY_COUNT), 0});

        // Shoot all of the rays in the direction of the camera but with horizontal offset
        for (size_t i = 0; i < RAY_COUNT; i++)
        {
            offset = ((float)i / (float)RAY_COUNT - 0.5f) * camera->fovy;
            rotationMatrix = MatrixRotateY(DEG2RAD * offset);
            ray_direction = Vector3Transform(direction, rotationMatrix);

            ray_direction = Vector3Normalize(ray_direction);

            ray = (Ray){camera->position, ray_direction};

            collision = bvh_tree_detect_collision_ray(tree, ray);
            if (collision.x != 0 && collision.y != 0 && collision.z != 0)
            {
                collisions[*collision_count] = collision;
                *collision_count = update_collisions(*collision_count);
            }
        }

        usleep(10000);
    }
}

void *animation_runner(void *args)
{
    LidarAnimationArgs *lidar_args = (LidarAnimationArgs *)args;
    animation_impl(lidar_args->tree, lidar_args->camera, lidar_args->collisions, lidar_args->collision_count);
    printf("thread done\n");
    pthread_detach(pthread_self());
    (*lidar_args->animating_lidar) = false;
    free(lidar_args);
    return NULL;
}

void lidar_animation(BVH_Tree *tree, Camera *camera, Vector3 *collisions, size_t *collision_count, bool *animating_lidar)
{
    pthread_t t1;
    LidarAnimationArgs *args = malloc(sizeof(LidarAnimationArgs));
    *args = (LidarAnimationArgs){tree, camera, collisions, collision_count, animating_lidar};
    pthread_create(&t1, NULL, animation_runner, args);
}