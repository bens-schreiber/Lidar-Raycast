#ifndef CAMERA_H_
#define CAMERA_H_

#include "raylib.h"

/// @brief A camera that can be moved around the scene with WASD
Camera *camera_create(void);

/// @brief Update the camera's position and target
static inline void camera_update(Camera *camera) {
    UpdateCamera(camera, CAMERA_FIRST_PERSON);
}

#endif // CAMERA_H_