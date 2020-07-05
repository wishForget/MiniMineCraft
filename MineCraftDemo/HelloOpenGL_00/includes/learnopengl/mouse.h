#ifndef _MOUSE_H

#include <GLFW/glfw3.h>

extern float xRotation, yRotation;
extern float scale;
extern float xTransl, yTransl;

extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
extern void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

#endif // !_MOUSE_H
