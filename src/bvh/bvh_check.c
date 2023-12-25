#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "../primitive/primitive.h"
#include "bvh.h"

#define is_leaf(node) (node->left == NULL && node->right == NULL)

// DFS, check each bounding box and primitives if they exist
unsigned char check_bvh_collision_impl(const BVH_Node *node, BoundingBox bounding_box)
{
    if (node == NULL)
    {
        return 0;
    }

    // If the bounding boxes intersect, this node is a candidate for collision
    if (CheckCollisionBoxes(node->bounding_box, bounding_box))
    {

        // Only a leaf will have primitives to check
        if (is_leaf(node))
        {

            // Check each primitive in the leaf node
            for (size_t i = 0; i < node->primitives_size; i++)
            {

                // If the primitive intersects the bounding box, there is a collision
                if (CheckCollisionBoxes(get_primitive_bounding_box(node->primitives[i]), bounding_box))
                {
                    return 1;
                }
            }
        }

        return check_bvh_collision_impl(node->left, bounding_box) || check_bvh_collision_impl(node->right, bounding_box);
    }

    return 0;
}

unsigned char check_bvh_collision(const BVH_Tree *tree, BoundingBox bounding_box)
{
    return check_bvh_collision_impl(tree->root, bounding_box);
}

// DFS, check each bounding box and primitives if they exist
Vector3 check_bvh_collision_ray_impl(const BVH_Node *node, Ray ray)
{
    if (node == NULL)
    {
        return Vector3Zero();
    }

    // If the ray hits a bounding box, this node is a candidate for collision
    if (GetRayCollisionBox(ray, node->bounding_box).hit)
    {

        // Only a leaf will have primitives to check
        if (is_leaf(node))
        {

            RayCollision collision;

            // Check each primitive in the leaf node
            for (size_t i = 0; i < node->primitives_size; i++)
            {
                collision = GetRayCollisionBox(ray, get_primitive_bounding_box(node->primitives[i]));

                // If the ray hits the primitive, there is a collision
                // Return the collision point
                if (collision.hit)
                {
                    return collision.point;
                }
            }
        }

        const Vector3 left = check_bvh_collision_ray_impl(node->left, ray);
        if (left.x != 0 && left.y != 0 && left.z != 0)
        {
            return left;
        }

        const Vector3 right = check_bvh_collision_ray_impl(node->right, ray);
        if (right.x != 0 && right.y != 0 && right.z != 0)
        {
            return right;
        }
    }

    return Vector3Zero();
}

Vector3 check_bvh_collision_ray(const BVH_Tree *tree, Ray ray)
{
    return check_bvh_collision_ray_impl(tree->root, ray);
}