#include <stdlib.h>
#include "raylib.h"
#include "../renderable/renderable.h"
#include "scene.h"

Renderable *create_scene(void)
{
    Renderable *renderables = malloc(sizeof(Renderable) * RENDERABLE_COUNT);
    for (int i = 0; i < RENDERABLE_COUNT; i++)
    {
        const int x = GetRandomValue(SCENE_AABB.min.x + RENDERABLE_DIMENSIONS.x, SCENE_AABB.max.x - RENDERABLE_DIMENSIONS.x);
        const int y = GetRandomValue(SCENE_AABB.min.y + RENDERABLE_DIMENSIONS.y, SCENE_AABB.max.y - RENDERABLE_DIMENSIONS.x);
        const int z = GetRandomValue(SCENE_AABB.min.z + RENDERABLE_DIMENSIONS.z, SCENE_AABB.max.z - RENDERABLE_DIMENSIONS.x);
        Vector3 centroid = (Vector3){x, y, z};
        renderables[i] = create_renderable(centroid, RED);
    }
    return renderables;
}

void draw_scene(Renderable renderables[RENDERABLE_COUNT])
{
    for (int i = 0; i < RENDERABLE_COUNT; i++)
    {
        draw_renderable(renderables[i]);
    }
}
