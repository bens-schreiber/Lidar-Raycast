#ifndef BVH_H
#define BVH_H

struct Renderable;
struct BoundingBox;
typedef size_t size_t;

typedef int (*qsort_compare)(const void *, const void *);
int compareX(const void *a, const void *b);
int compareY(const void *a, const void *b);
int compareZ(const void *a, const void *b);

qsort_compare compare_by_longest_axis(BoundingBox scene_aabb);

BoundingBox expand_aabb(BoundingBox a, BoundingBox b);

// Draws a Bounding Volume Hierarchy without using a BVH tree.
void draw_bvh_aabb(Renderable *renderable, size_t renderable_size, BoundingBox scene_aabb);

#endif // BVH_H