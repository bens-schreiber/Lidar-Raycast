#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "raylib.h"
#include "../renderable/renderable.h"
#include "bvh.h"

int compareX(const void *a, const void *b)
{

    Renderable *renderable_a = (Renderable *)a;
    Renderable *renderable_b = (Renderable *)b;

    return renderable_a->centroid.x - renderable_b->centroid.x;
}

int compareY(const void *a, const void *b)
{

    Renderable *renderable_a = (Renderable *)a;
    Renderable *renderable_b = (Renderable *)b;

    return renderable_a->centroid.y - renderable_b->centroid.y;
}

int compareZ(const void *a, const void *b)
{

    Renderable *renderable_a = (Renderable *)a;
    Renderable *renderable_b = (Renderable *)b;

    return renderable_a->centroid.z - renderable_b->centroid.z;
}

qsort_compare compare_by_longest_axis(BoundingBox scene_aabb)
{
    // We need to determine the longest axis of the scene_aabb BoundingBox.
    // The bounding box gives two 3D cartesian points, min and max.
    // There are three axis to consider: x, y, z.
    float x_distance = scene_aabb.max.x - scene_aabb.min.x;
    float y_distance = scene_aabb.max.y - scene_aabb.min.y;
    float z_distance = scene_aabb.max.z - scene_aabb.min.z;

    if (x_distance > y_distance && x_distance > z_distance)
    {
        return compareX;
    }
    if (y_distance > x_distance && y_distance > z_distance)
    {
        return compareY;
    }
    return compareZ;
}

BoundingBox expand_aabb(BoundingBox a, BoundingBox b) {
    BoundingBox result;

    // For each dimension, the lower bound of the result is the minimum of the lower bounds of a and b.
    result.min.x = fmin(a.min.x, b.min.x);
    result.min.y = fmin(a.min.y, b.min.y);
    result.min.z = fmin(a.min.z, b.min.z);

    // For each dimension, the upper bound of the result is the maximum of the upper bounds of a and b.
    result.max.x = fmax(a.max.x, b.max.x);
    result.max.y = fmax(a.max.y, b.max.y);
    result.max.z = fmax(a.max.z, b.max.z);

    return result;
}

// Draws a Bounding Volume Hierarchy without using a BVH tree.
// For learning purposes.
void draw_bvh_aabb(Renderable *renderable, size_t renderable_size, BoundingBox scene_aabb)
{

    if (renderable_size < 2)
        return;

    DrawBoundingBox(scene_aabb, BLACK);

    // Sort the renderables by the longest axis.
    Renderable *axis_sorted = memcpy(malloc(sizeof(Renderable) * renderable_size), renderable, sizeof(Renderable) * renderable_size);
    qsort(axis_sorted, renderable_size, sizeof(Renderable), compare_by_longest_axis(scene_aabb));

    // Find the median of the renderables.
    size_t median = renderable_size / 2;
    Renderable median_renderable = axis_sorted[median];

    // Calculate the left AABB.
    // It should contain all renderables from 0 to median.
    BoundingBox left_aabb = get_renderable_bounding_box(median_renderable);
    for (size_t i = 0; i <= median; i++) {
        left_aabb = expand_aabb(left_aabb, get_renderable_bounding_box(axis_sorted[i]));
    }

    // Calculate the right AABB.
    // It should contain all renderables from median to renderable_size.
    BoundingBox right_aabb = get_renderable_bounding_box(median_renderable);
    for (size_t i = median + 1; i < renderable_size; i++) {
        right_aabb = expand_aabb(right_aabb, get_renderable_bounding_box(axis_sorted[i]));
    }
    

    // Recurse on the left and right AABBs.
    draw_bvh_aabb(axis_sorted, median, left_aabb);
    draw_bvh_aabb(axis_sorted + median, renderable_size - median, right_aabb);


    free(axis_sorted);
}