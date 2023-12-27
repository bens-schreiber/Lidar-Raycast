#include <stdlib.h>
#include "raylib.h"
#include "../primitive/primitive.h"
#include "bvh.h"

void draw_bvh_tree_impl(const BVH_Node *node)
{
    if (node == NULL)
    {
        return;
    }

    DrawBoundingBox(node->bounding_box, BLACK);

    for (size_t i = 0; i < node->primitives_size; i++)
    {
        primitive_draw(&node->primitives[i]);
        DrawBoundingBox(primitive_get_bounding_box(&node->primitives[i]), BLACK);
    }

    draw_bvh_tree_impl(node->left);
    draw_bvh_tree_impl(node->right);
}

void draw_bvh_tree(const BVH_Tree *tree)
{
    draw_bvh_tree_impl(tree->root);
}