#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "raylib.h"

#define PRIMITIVE_DIMENSIONS (Vector3){1.0f, 1.0f, 1.0f}

// Some geometric primitive that can be rendered (e.g. a cube)
typedef struct Primitive
{
    Vector3 centroid;
    Color color;
} Primitive;

BoundingBox get_primitive_bounding_box(Primitive primitive);

Primitive create_primitive(Vector3 centroid, Color color);

void draw_primitive(Primitive primitive);

#endif // PRIMITIVE_H
