#include <stdlib.h>
#include "raylib.h"
#include "../renderable/renderable.h"
#include "bvh.h"

BVH_Tree *build_bvh_tree(Renderable *renderable, size_t renderable_size, BoundingBox scene_aabb)
{
    BVH_Tree *tree = malloc(sizeof(BVH_Tree));
    tree->root = build_bvh_tree_impl(renderable, renderable_size, scene_aabb);
    return tree;
}

void draw_bvh_tree_impl(BVH_Node *node)
{
    if (node == NULL)
    {
        return;
    }

    DrawBoundingBox(node->bounding_box, BLACK);

    draw_bvh_tree_impl(node->left);
    draw_bvh_tree_impl(node->right);
}

void draw_bvh_tree(BVH_Tree *tree)
{
    draw_bvh_tree_impl(tree->root);
}