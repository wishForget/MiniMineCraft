#include <glm/gtc/matrix_transform.hpp>
#include "mouse.h"

float xRotation = 0.0f, yRotation = 0.0f;
float scale = 1.0f;
float xTransl = 0.0f, yTransl = 0.0f;

const float rotSpeed = glm::pi<float>() / 180.0f / 32.0f;
float translSpeed = 0.05f;

bool bLButtonDown = false, bMButtonDown = false, bRButtonDown = false;
float lastX, lastY;
float lastScl = 1.0f;

bool firstMouse = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:

		bLButtonDown = action == GLFW_PRESS;
		break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
		bMButtonDown = action == GLFW_PRESS;

		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
		bRButtonDown = action == GLFW_PRESS;
		break;

	default:
		break;
	}

	if (bLButtonDown || bMButtonDown || bRButtonDown)
		firstMouse = true;
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;

		if (bMButtonDown)
			lastScl = scale;

		firstMouse = false;
	}

	float dx = xpos - lastX;
	float dy = ypos - lastY;

	if (bLButtonDown) {
		yRotation += dx * rotSpeed;
		xRotation += dy * rotSpeed;
	}
	if (bRButtonDown) {
		if (dy > 0.0f) {
			dy = sqrt(dy);
			scale = lastScl * dy;
		}
		else if (dy < 0.0f) {
			dy = sqrt(-dy);
			scale = lastScl / dy;
		}
	}

	if (bMButtonDown) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		float rx = translSpeed / (0.5f * width) /*/ scale*/;
		xTransl += dx * rx;
		float ry = translSpeed / (0.5f * height) /*/ scale*/;
		yTransl -= dy * ry;
	}
}
