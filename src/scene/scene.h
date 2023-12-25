#ifndef SCENE_H
#define SCENE_H

// How many primitives are in the scene
#define PRIMITIVE_COUNT 30

struct Primitive;
struct BoundingBox;
struct Vector3;

// Size of the scene
#define SCENE_BOUNDING_BOX                                             \
    (struct BoundingBox)                                               \
    {                                                                  \
        (struct Vector3){-10, 0, -10}, (struct Vector3) { 10, 10, 10 } \
    }

struct Primitive *create_scene(void);

void draw_scene(struct Primitive primitives[PRIMITIVE_COUNT]);

#endif // SCENE_H