#ifndef LONGEST_AXIS_H_
#define LONGEST_AXIS_H_

struct BoundingBox;

typedef int (*qsort_compare)(const void *, const void *);

extern inline int compareX(const void *a, const void *b);

extern inline int compareY(const void *a, const void *b);

extern inline int compareZ(const void *a, const void *b);

/// @brief Determines which axis is the longest in a bounding box
/// @param scene_aabb 
/// @return a function for the axis longest to sort by
qsort_compare compare_by_longest_axis(struct BoundingBox scene_aabb);

#endif // LONGEST_AXIS_H_