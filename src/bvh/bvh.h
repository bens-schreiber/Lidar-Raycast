#ifndef BVH_H
#define BVH_H

#include <stddef.h>

struct Primitive;
struct BoundingBox;
struct Ray;

/// @brief A node in a BVH tree
/// @param left: the left child of the node
/// @param right: the right child of the node
/// @param bounding_box: the bounding box enclosing the nodes primitives
/// @param primitives: the primitives enclosed by the node
/// @param primitives_size: the amount of primitives enclosed by the node (0 if non leaf node)
typedef struct BVH_Node
{
    struct BVH_Node *left;
    struct BVH_Node *right;
    struct BoundingBox bounding_box;
    struct Primitive primitives[2];
    size_t primitives_size;
} BVH_Node;

/// @brief A Bounding Volume Hierarchy Tree, log n collision detection
typedef struct BVH_Tree
{
    BVH_Node *root;
} BVH_Tree;

/// @brief Builds a BVH tree from a list of primitives and a scene
/// @param primitives All primitives in the scene
/// @param primitives_size The amount of primitives in the scene
/// @param scene_aabb The bounding box enclosing the entire scene
/// @return A pointer to the BVH tree
BVH_Tree *bvh_tree_create(const struct Primitive *primitives, size_t primitives_size, struct BoundingBox scene_aabb);

BVH_Node *bvh_tree_create_impl(const struct Primitive *primitives, size_t primitives_size, struct BoundingBox bounding_box);

/// @brief Frees all the nodes in a BVH tree
/// @param tree the BVH tree to free
void bvh_tree_free(BVH_Tree *tree);

/// @brief Checks for collisions between a bounding box and a BVH tree
/// @param tree The BVH tree to check collisions with
/// @param bounding_box The BoundingBox to check collisions against the tree
/// @return 1 if there is a collision, 0 otherwise
unsigned char bvh_tree_detect_collision(const BVH_Tree *tree, struct BoundingBox bounding_box);

/// @brief Checks for collisions between a ray and a BVH tree
/// @param tree The BVH tree to check collisions with
/// @param ray The Ray to check collisions against the tree
/// @return The point of collision if there is a collision, (0, 0, 0) otherwise
Vector3 bvh_tree_detect_collision_ray(const BVH_Tree *tree, struct Ray ray);

/// @brief Draws all of the bounding boxes and primitives in a BVH tree
void draw_bvh_tree(const BVH_Tree *tree);

#endif // BVH_H