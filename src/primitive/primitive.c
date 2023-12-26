#include "primitive.h"
#include "raymath.h"

#define HALF_PRIMITIVE_DIMENSIONS Vector3Scale(PRIMITIVE_DIMENSIONS, 0.5f)

BoundingBox primitive_get_bounding_box(Primitive primitive)
{
    Vector3 min = Vector3Subtract(primitive.centroid, HALF_PRIMITIVE_DIMENSIONS);
    Vector3 max = Vector3Add(primitive.centroid, HALF_PRIMITIVE_DIMENSIONS);
    return (BoundingBox){min, max};
}