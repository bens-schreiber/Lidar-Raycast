#include "raylib.h"
#include "longest_axis.h"
#include "../renderable/renderable.h"

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