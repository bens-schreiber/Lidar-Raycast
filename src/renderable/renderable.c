#include "renderable.h"
#include "raymath.h"

BoundingBox get_renderable_bounding_box(Renderable renderable)
{
    Vector3 halfSize = Vector3Scale(RENDERABLE_DIMENSIONS, 0.5f);
    Vector3 min = Vector3Subtract(renderable.centroid, halfSize);
    Vector3 max = Vector3Add(renderable.centroid, halfSize);
    return (BoundingBox){min, max};
}

Renderable create_renderable(Vector3 centroid, Color color)
{
    return (Renderable){centroid, color};
}

void draw_renderable(Renderable renderable)
{
    Vector3 center = renderable.centroid;
    DrawCubeV(center, RENDERABLE_DIMENSIONS, renderable.color);
    DrawCubeWiresV(center, RENDERABLE_DIMENSIONS, BLACK);
}