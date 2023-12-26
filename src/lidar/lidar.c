
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../primitive/primitive.h"
#include "../bvh/bvh.h"
#include "raymath.h"
#include "lidar.h"

typedef struct
{
    BVH_Tree *tree;
    Camera *camera;
    Vector3 *collisions;
    size_t *collision_count;
    bool *animating_lidar;
} LidarAnimationArgs;

void _lidar_animation_impl(BVH_Tree *tree, Camera *camera, Vector3 *collisions, size_t *collision_count)
{

    // Direction camera is looking in
    Vector3 direction = Vector3Subtract(camera->target, camera->position);
    direction = Vector3Normalize(direction);

    Ray ray;

    // vertical offset of lidar
    for (float v = 0; v < RAY_COUNT; v++)
    {
        direction = Vector3Add(direction, (Vector3){0, 0 - direction.y + (v/RAY_COUNT), 0});

        // Shoot all of the rays in the direction of the camera but with horizontal offset
        for (size_t i = 0; i < RAY_COUNT; i++)
        {
            float offset = ((float)i / (float)RAY_COUNT - 0.5f) * camera->fovy;
            Matrix rotationMatrix = MatrixRotateY(DEG2RAD * offset);
            Vector3 ray_direction = Vector3Transform(direction, rotationMatrix);

            ray_direction = Vector3Normalize(ray_direction);

            ray = (Ray){camera->position, ray_direction};

            Vector3 collision = check_bvh_collision_ray(tree, ray);
            if (collision.x != 0 && collision.y != 0 && collision.z != 0)
            {
                collisions[*collision_count] = collision;
                (*collision_count)++;
            }
        }

        // usleep(10000);
    }
}

void *_lidar_animation(void *args)
{
    LidarAnimationArgs *lidar_args = (LidarAnimationArgs *)args;
    _lidar_animation_impl(lidar_args->tree, lidar_args->camera, lidar_args->collisions, lidar_args->collision_count);
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
    pthread_create(&t1, NULL, _lidar_animation, args);
}