#ifndef LIDAR_H
#define LIDAR_H

#define RAY_COUNT 500.0f

struct BVH_Tree;
struct Camera;
struct Vector3;

void lidar_animation(BVH_Tree *tree, Camera *camera, Vector3 *collisions, size_t *collision_count, bool *animating_lidar);

#endif // LIDAR_H