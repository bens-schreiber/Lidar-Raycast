#ifndef BVH_H
#define BVH_H

struct Renderable;
struct BoundingBox;
typedef size_t size_t;

typedef struct BVH_Node
{
    struct BVH_Node *left;
    struct BVH_Node *right;
    struct BoundingBox bounding_box;
    struct Renderable *renderable;
} BVH_Node;

typedef struct BVH_Tree
{
    BVH_Node *root;
} BVH_Tree;

// Builds a BVH tree from a list of renderables and a scene
BVH_Tree *build_bvh_tree(struct Renderable *renderable, size_t renderable_size, struct BoundingBox scene_aabb);

BVH_Node *build_bvh_tree_impl(Renderable *renderable, size_t renderable_size, BoundingBox bounding_box);

void draw_bvh_tree(BVH_Tree *tree);

#endif // BVH_H