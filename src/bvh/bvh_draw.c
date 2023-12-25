#include <stdlib.h>
#include "raylib.h"
#include "../primitive/primitive.h"
#include "bvh.h"

// DFS, draw each bounding box and primitives if they exist
void draw_bvh_tree_impl(BVH_Node *node)
{
    if (node == NULL)
    {
        return;
    }

    DrawBoundingBox(node->bounding_box, BLACK);

    for (size_t i = 0; i < node->primitives_size; i++)
    {
        draw_primitive(node->primitives[i]);
        DrawBoundingBox(get_primitive_bounding_box(node->primitives[i]), BLACK);
    }

    draw_bvh_tree_impl(node->left);
    draw_bvh_tree_impl(node->right);
}

void draw_bvh_tree(BVH_Tree *tree)
{
    draw_bvh_tree_impl(tree->root);
}