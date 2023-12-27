#ifndef LIDAR_H
#define LIDAR_H

/// The amount of rays to shoot horizontally
/// @note This is the amount of rays shot in one frame
/// @note Despite being a float, this value should be discrete. Float just prevents casting.
#define RAY_COUNT 300.0f

struct BVH_Tree;
struct Camera;
struct Vector3;

/// Shoots rays from the camera position and logs collisions with Vector3 coordinates.
/// Runs on a seperate thread.
/// @param tree: the BVH tree to detect collisions with
/// @param camera: the camera to shoot rays from
/// @param collisions: the array to log collisions in
/// @param collision_count: the amount of collisions logged
/// @param animating_lidar: whether or not the lidar is animating. Will be set to false when thread is done.
void lidar_animation(const BVH_Tree *tree, const volatile Camera *camera, volatile Vector3 *collisions, volatile size_t *collision_count, volatile bool *animating_lidar);

#endif // LIDAR_H