#include <stdlib.h>
#include "raylib.h"
#include "../primitive/primitive.h"
#include "scene.h"

Primitive *scene_create(void)
{
    Primitive *primitives = malloc(sizeof(Primitive) * PRIMITIVE_COUNT);
    int x, y, z;
    for (int i = 0; i < PRIMITIVE_COUNT; i++)
    {
        x = GetRandomValue(SCENE_BOUNDING_BOX.min.x + PRIMITIVE_DIMENSIONS.x, SCENE_BOUNDING_BOX.max.x - PRIMITIVE_DIMENSIONS.x);
        y = GetRandomValue(SCENE_BOUNDING_BOX.min.y + PRIMITIVE_DIMENSIONS.y, SCENE_BOUNDING_BOX.max.y - PRIMITIVE_DIMENSIONS.x);
        z = GetRandomValue(SCENE_BOUNDING_BOX.min.z + PRIMITIVE_DIMENSIONS.z, SCENE_BOUNDING_BOX.max.z - PRIMITIVE_DIMENSIONS.x);
        primitives[i] = primitive_create((Vector3){x, y, z}, RED);
    }
    return primitives;
}

void scene_draw(Primitive primitives[PRIMITIVE_COUNT])
{
    for (int i = 0; i < PRIMITIVE_COUNT; i++)
    {
        primitive_draw(primitives[i]);
    }
}
