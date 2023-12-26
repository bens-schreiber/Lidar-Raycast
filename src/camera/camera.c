#include <stdlib.h>
#include "camera.h"

Camera *create_camera()
{
    Camera *camera = malloc(sizeof(Camera));
    camera->position = (Vector3){0.0f, 2.0f, 4.0f};
    camera->target = (Vector3){0.0f, 2.0f, 0.0f};
    camera->up = (Vector3){0.0f, 1.0f, 0.0f};
    camera->fovy = 60.0f;
    camera->projection = CAMERA_PERSPECTIVE;
    return camera;
}

void update_camera(Camera *camera)
{
    UpdateCamera(camera, CAMERA_FIRST_PERSON);
}