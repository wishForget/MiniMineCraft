#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GLU.h>
#include <learnopengl/camera.h>
#include "AABB.h"

static class Control
{
public:
	Control();
	~Control();
	void static init(int width, int height, Camera* camera, bool ifDebug);
	void static buffer_resize_callback(GLFWwindow* window, int width, int height);
	void static mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void static scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void static mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void static processInput(GLFWwindow *window);
	void static setCurMousePos(float _xpos, float _ypos);
	void static pick();
	void static build();
	int static DetectRayPolygon(glm::vec3 startPoint, glm::vec3 inAABBPoint,glm::vec3 testDir, glm::vec3 border);


	static Camera* camera;
	static bool debug;
	static bool firstMouse;
	static float deltaTime;
	static float lastFrame;
	static float xpos;
	static float ypos;
	static int SCR_WIDTH, SCR_HEIGHT;
	static float lastX;
	static float lastY;
	static float Myzpos;
	static float Myxpos;
	static float Myypos;
	static bool mouseDown;
};

