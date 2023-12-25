#include <stdlib.h>
#include "raylib.h"
#include "../primitive/primitive.h"
#include "scene.h"

// Creates a scene with PRIMITIVE_COUNT number of primitives
// Randomly places them within the SCENE_BOUNDING_BOX
//
// Returns a pointer to the array of primitives
Primitive *create_scene(void)
{
    Primitive *primitives = malloc(sizeof(Primitive) * PRIMITIVE_COUNT);
    for (int i = 0; i < PRIMITIVE_COUNT; i++)
    {
        const int x = GetRandomValue(SCENE_BOUNDING_BOX.min.x + PRIMITIVE_DIMENSIONS.x, SCENE_BOUNDING_BOX.max.x - PRIMITIVE_DIMENSIONS.x);
        const int y = GetRandomValue(SCENE_BOUNDING_BOX.min.y + PRIMITIVE_DIMENSIONS.y, SCENE_BOUNDING_BOX.max.y - PRIMITIVE_DIMENSIONS.x);
        const int z = GetRandomValue(SCENE_BOUNDING_BOX.min.z + PRIMITIVE_DIMENSIONS.z, SCENE_BOUNDING_BOX.max.z - PRIMITIVE_DIMENSIONS.x);
        Vector3 centroid = (Vector3){x, y, z};
        primitives[i] = create_primitive(centroid, RED);
    }
    return primitives;
}

void draw_scene(Primitive primitives[PRIMITIVE_COUNT])
{
    for (int i = 0; i < PRIMITIVE_COUNT; i++)
    {
        draw_primitive(primitives[i]);
    }
}
