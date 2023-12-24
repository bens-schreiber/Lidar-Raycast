#ifndef SCENE_H
#define SCENE_H

#define RENDERABLE_COUNT 5

struct Renderable;
struct BoundingBox;

#define SCENE_AABB                                       \
    (BoundingBox)                                        \
    {                                                    \
        (Vector3){-20, 0, -20}, (Vector3) { 20, 20, 20 } \
    }

Renderable *create_scene(void);

void draw_scene(Renderable renderables[RENDERABLE_COUNT]);

#endif // SCENE_H