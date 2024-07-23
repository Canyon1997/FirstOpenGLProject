#pragma once

// OpenGL
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/// @brief Moment user resizes the window, viewport should b e adjusted as well
///    Callback function that gets called each time window is resized
/// @param window
///    Window to be resized
/// @param width
///    Width the window should be set to
/// @param height
///    Height the window should be set to
void framebuffer_size_callback(GLFWwindow* window, int width, int height);