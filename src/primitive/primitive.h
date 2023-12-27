#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "raylib.h"

#define PRIMITIVE_DIMENSIONS \
    (Vector3) { 1.0f, 1.0f, 1.0f }

/// Some geometric primitive that can be rendered (e.g. a cube)
/// @param centroid: the center of the primitive, rendered around this point
/// @param color: the whole color of the primitive
typedef struct Primitive
{
    Vector3 centroid;
    Color color;
} Primitive;

/// @returns The bounding box enclosing a primitive
BoundingBox primitive_get_bounding_box(const Primitive *primitive);

/// Create a primitive
/// @param centroid: the center of the primitive, rendered around this point
static inline Primitive primitive_create(Vector3 centroid, Color color)
{
    return (Primitive){centroid, color};
}

/// Render a primitive around its centroid
static inline void primitive_draw(const Primitive *primitive)
{
    DrawCubeV(primitive->centroid, PRIMITIVE_DIMENSIONS, primitive->color);
}

#endif // PRIMITIVE_H
