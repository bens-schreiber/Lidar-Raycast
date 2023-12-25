#include "primitive.h"
#include "raymath.h"

// Creates an AABB (boudning box) enclosing the primitive
BoundingBox get_primitive_bounding_box(Primitive primitive)
{
    // Since the centroid is the center of the primitive,
    // the min and max points are just the centroid +/- half the dimensions
    const Vector3 halfSize = Vector3Scale(PRIMITIVE_DIMENSIONS, 0.5f);

    Vector3 min = Vector3Subtract(primitive.centroid, halfSize);
    Vector3 max = Vector3Add(primitive.centroid, halfSize);

    return (BoundingBox){min, max};
}

// Creates a primitive from its center most position and a color
Primitive create_primitive(Vector3 centroid, Color color)
{
    return (Primitive){centroid, color};
}

// Draws the primitive
void draw_primitive(Primitive primitive)
{
    Vector3 center = primitive.centroid;
    DrawCubeV(center, PRIMITIVE_DIMENSIONS, primitive.color);
}