#ifndef BVH_H
#define BVH_H

struct Primitive;
struct BoundingBox;
struct Ray;
typedef size_t size_t;

typedef struct BVH_Node
{
    struct BVH_Node *left;
    struct BVH_Node *right;
    struct BoundingBox bounding_box;
    struct Primitive primitives[2];
    size_t primitives_size;
} BVH_Node;

// Bounding Volume Hierarchy Tree
typedef struct BVH_Tree
{
    BVH_Node *root;
} BVH_Tree;

// Builds a BVH tree from a list of primitives and a scene
BVH_Tree *build_bvh_tree(const struct Primitive *primitives, size_t primitives_size, struct BoundingBox scene_aabb);

BVH_Node *build_bvh_tree_impl(const struct Primitive *primitives, size_t primitives_size, struct BoundingBox bounding_box);

// Checks for collisions between a bounding box and a BVH tree.
// Returns 1 if there is a collision, 0 otherwise.
unsigned char check_bvh_collision(const BVH_Tree *tree, struct BoundingBox bounding_box);

// Checks for collisions between a ray and a BVH tree.
// Returns the collision point if there is a collision, Vector3Zero() otherwise.
Vector3 check_bvh_collision_ray(const BVH_Tree *tree, struct Ray ray);

void draw_bvh_tree(BVH_Tree *tree);

#endif // BVH_H