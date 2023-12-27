
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../consts.h"
#include "../primitive/primitive.h"
#include "../bvh/bvh.h"
#include "../scene/scene.h"
#include "raymath.h"
#include "lidar.h"

/// @brief  Args for the lidar animation thread
typedef struct
{
    const BVH_Tree *tree;
    const volatile Camera *camera;
    volatile Vector3 *collisions;
    volatile size_t *collision_count;
    volatile bool *animating_lidar;
} LidarAnimationArgs;

/// There can be at most MAX_COLLISIONS
#define max_collisions(collision) Clamp(collision, 0, MAX_COLLISIONS)

/// Index of the next collision to write to.
/// This index in tandem with update_write_index() allows for a circular buffer
int write_index = 0;

/// @brief Updates the collision count to stay within the bounds of the array, resetting to 0 on overflow
/// @param collision The current collision count
/// @return The updated collision count
#define update_write_index(collision) (collision + 1) % MAX_COLLISIONS

void animation_impl(const BVH_Tree *tree, const volatile Camera *camera, volatile Vector3 *collisions, volatile size_t *collision_count)
{

    Vector3 direction, collision, ray_direction;
    float offset;
    Matrix rotationMatrix;
    Ray ray;

    for (float vertical = -100; vertical < SCREEN_HEIGHT; vertical++)
    {
        // Direction camera is looking in.
        // Recalculate after every thread sleep to account for camera movement
        direction = Vector3Subtract(camera->target, camera->position);
        direction = Vector3Normalize(direction);
        direction = Vector3Add(direction, (Vector3){0, 0 - direction.y + (vertical / RAY_COUNT), 0});

        // Shoot all of the rays in the direction of the camera but with horizontal offset
        for (float horizontal = 0; horizontal < RAY_COUNT; horizontal++)
        {
            offset = (horizontal / RAY_COUNT - 0.5f) * camera->fovy;
            rotationMatrix = MatrixRotateY(DEG2RAD * offset);
            ray_direction = Vector3Transform(direction, rotationMatrix);

            ray_direction = Vector3Normalize(ray_direction);

            ray = (Ray){camera->position, ray_direction};

            collision = bvh_tree_detect_collision_ray(tree, ray);
            if (collision.x != 0 && collision.y != 0 && collision.z != 0)
            {
                collisions[write_index] = collision;
                *collision_count = max_collisions(*collision_count + 1);
                write_index = update_write_index(write_index);
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

void lidar_animation(const BVH_Tree *tree, const volatile Camera *camera, volatile Vector3 *collisions, volatile size_t *collision_count, volatile bool *animating_lidar)
{
    pthread_t t1;
    LidarAnimationArgs *args = malloc(sizeof(LidarAnimationArgs));
    *args = (LidarAnimationArgs){tree, camera, collisions, collision_count, animating_lidar};
    pthread_create(&t1, NULL, animation_runner, args);
}