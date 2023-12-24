#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "raylib.h"

#define RENDERABLE_DIMENSIONS (Vector3){1.0f, 1.0f, 1.0f}

typedef struct Renderable
{
    Vector3 centroid;
    Color color;
} Renderable;

BoundingBox get_renderable_bounding_box(Renderable renderable);

Renderable create_renderable(Vector3 centroid, Color color);

void draw_renderable(Renderable renderable);

#endif // RENDERABLE_H
