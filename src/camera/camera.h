#ifndef CAMERA_H_
#define CAMERA_H_

#include "raylib.h"

// A camera that can be moved around the scene
Camera create_camera();

// Update the camera's position and target
void update_camera(Camera *camera);

#endif // CAMERA_H_