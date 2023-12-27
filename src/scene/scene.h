#ifndef SCENE_H
#define SCENE_H

/// Amount of primitives to be rendered
#define PRIMITIVE_COUNT 100

/// Enclosing bounding box of the entire scene.
/// All primitives will be rendered within this box.
#define SCENE_BOUNDING_BOX                                             \
    (struct BoundingBox)                                               \
    {                                                                  \
        (struct Vector3){-10, 0, -10}, (struct Vector3) { 10, 10, 10 } \
    }

struct Primitive;
struct BoundingBox;
struct Vector3;

/// Creates a list of PRIMITIVE_COUNT primitives with centroids within SCENE_BOUNDING_BOX.
struct Primitive *scene_create(void);

/// Renders all primitives in the scene around their centroids.
void scene_draw(const struct Primitive primitives[PRIMITIVE_COUNT]);

#endif // SCENE_H