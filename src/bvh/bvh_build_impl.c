#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "longest_axis.h"
#include "raylib.h"
#include "../renderable/renderable.h"
#include "bvh.h"

BoundingBox expand_aabb(BoundingBox a, BoundingBox b)
{
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

BVH_Node *build_bvh_tree_impl(Renderable *renderable, size_t renderable_size, BoundingBox bounding_box)
{

    if (renderable_size < 2)
    {
        return NULL;
    }

    // Create the new node for the BVH tree
    BVH_Node *new_node = malloc(sizeof(BVH_Node));
    new_node->bounding_box = bounding_box;

    // Sort the renderables by the longest axis.
    Renderable *axis_sorted = memcpy(malloc(sizeof(Renderable) * renderable_size), renderable, sizeof(Renderable) * renderable_size);
    qsort(axis_sorted, renderable_size, sizeof(Renderable), compare_by_longest_axis(bounding_box));

    // Find the median of the renderables.
    size_t median = renderable_size / 2;
    Renderable median_renderable = axis_sorted[median];

    // Calculate the left AABB.
    // It should contain all renderables from 0 to median.
    BoundingBox left_aabb = get_renderable_bounding_box(median_renderable);
    for (size_t i = 0; i <= median; i++)
    {
        left_aabb = expand_aabb(left_aabb, get_renderable_bounding_box(axis_sorted[i]));
    }

    // Calculate the right AABB.
    // It should contain all renderables from median to renderable_size.
    BoundingBox right_aabb = get_renderable_bounding_box(median_renderable);
    for (size_t i = median + 1; i < renderable_size; i++)
    {
        right_aabb = expand_aabb(right_aabb, get_renderable_bounding_box(axis_sorted[i]));
    }

    // Recurse on the left and right AABBs.
    new_node->left = build_bvh_tree_impl(axis_sorted, median, left_aabb);
    new_node->right = build_bvh_tree_impl(axis_sorted + median, renderable_size - median, right_aabb);

    free(axis_sorted);

    return new_node;
}
