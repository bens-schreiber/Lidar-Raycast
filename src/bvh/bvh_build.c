#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./util/longest_axis.h"
#include "raylib.h"
#include "../primitive/primitive.h"
#include "bvh.h"

void free_bvh_node(BVH_Node *node)
{
    if (node == NULL)
    {
        return;
    }

    free_bvh_node(node->left);
    free_bvh_node(node->right);
    free(node);
}

void free_bvh_tree(BVH_Tree *tree)
{
    free_bvh_node(tree->root);
    free(tree);
}
// Creates a BVH Tree from the given primitives, and the scenes bounding box
BVH_Tree *build_bvh_tree(const Primitive *primitives, size_t primitives_size, BoundingBox scene_aabb)
{
    BVH_Tree *tree = malloc(sizeof(BVH_Tree));
    tree->root = build_bvh_tree_impl(primitives, primitives_size, scene_aabb);
    return tree;
}

// Expands a bounding box of a to contain b
// Returns the expanded bounding box
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

// Creates a BVH node from the given primitives and bounding box
BVH_Node *create_bvh_node(const Primitive *primitives, size_t primitives_size, BoundingBox bounding_box)
{
    BVH_Node *new_node = malloc(sizeof(BVH_Node));
    new_node->bounding_box = bounding_box;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->primitives_size = 0;

    if (primitives_size == 1)
    {
        new_node->primitives[0] = primitives[0];
        new_node->primitives[1] = primitives[0];
        new_node->primitives_size = 1;
        return new_node;
    }

    if (primitives_size == 2)
    {
        new_node->primitives[0] = primitives[0];
        new_node->primitives[1] = primitives[1];
        new_node->primitives_size = 2;
        return new_node;
    }

    return new_node;
}

BVH_Node *build_bvh_tree_impl(const Primitive *primitives, size_t primitives_size, BoundingBox bounding_box)
{

    // If there are less than 2 primitives, the BVH node should be a leaf node, and contain the primitives.
    if (primitives_size < 2)
    {
        return NULL;
    }

    BVH_Node *new_node = create_bvh_node(primitives, primitives_size, bounding_box);

    // Sort the primitivess by the longest axis.
    Primitive *axis_sorted = memcpy(malloc(sizeof(Primitive) * primitives_size), primitives, sizeof(Primitive) * primitives_size);
    qsort(axis_sorted, primitives_size, sizeof(Primitive), compare_by_longest_axis(bounding_box));

    // Find the median of the primitivess.
    size_t median = primitives_size / 2;
    Primitive median_primitives = axis_sorted[median];

    // Calculate the left AABB.
    // It should contain all primitivess from 0 to median.
    BoundingBox left_aabb = get_primitive_bounding_box(median_primitives);
    for (size_t i = 0; i <= median; i++)
    {
        left_aabb = expand_aabb(left_aabb, get_primitive_bounding_box(axis_sorted[i]));
    }

    // Calculate the right AABB.
    // It should contain all primitivess from median to primitives_size.
    BoundingBox right_aabb = get_primitive_bounding_box(median_primitives);
    for (size_t i = median + 1; i < primitives_size; i++)
    {
        right_aabb = expand_aabb(right_aabb, get_primitive_bounding_box(axis_sorted[i]));
    }

    // Recurse on the left and right AABBs.
    new_node->left = build_bvh_tree_impl(axis_sorted, median, left_aabb);
    new_node->right = build_bvh_tree_impl(axis_sorted + median, primitives_size - median, right_aabb);

    free(axis_sorted);

    return new_node;
}
