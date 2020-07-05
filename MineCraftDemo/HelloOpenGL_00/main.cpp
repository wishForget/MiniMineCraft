#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <vector>
#include <filesystem>
#include "mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "SkyDome.h"
#include "Control.h"
#include "Model.h"
#include "Chunk.h"
#include "WorldInfo.h"
#include "BlockGenerator.h"
#include "noise.h"
#include "SingletonShader.h"
#include "World.h"

using namespace std;
const bool debug = true;
int SCR_WIDTH = 1600, SCR_HEIGHT = 800;

SkyDome* skyDome = nullptr;
Camera* camera = nullptr;
glm::vec3 lightPos = glm::vec3(14.0f, 40.0f, 18.0f);
bool ifClick = false;
glm::mat4 views;
glm::mat4 projects;

void initGame() {
	try {
		skyDome = new SkyDome(
			"./resources/skyDome/blueSkyWithCloud",
			"Cam_2_Left+X.png", "Cam_3_Right-X.png",
			"Cam_4_Up+Y.png", "Cam_5_Down-Y.png",
			"Cam_0_Front+Z.png", "Cam_1_Back-Z.png",
			"./shader/skyDome.vs", "./shader/skyDome.fs");
		skyDome->init();
		cout << "天顶球加载完毕" << endl;
	}
	catch (std::bad_alloc) {
		cout << "天顶球加载出现错误" << endl;
	}
	camera = new Camera(glm::vec3(rand()%180, 40.0f, rand()%180));
	Control::init(SCR_WIDTH, SCR_HEIGHT, camera, true);
	WorldInfo::lastUpdatePostion = camera->Position;
	
}



int main(int nargs, char *args[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, args[0], NULL, NULL);
	glfwSetFramebufferSizeCallback(window, (Control::buffer_resize_callback));
	glfwSetCursorPosCallback(window, (Control::mouse_callback));
	glfwSetScrollCallback(window, (Control::scroll_callback));
	glfwSetMouseButtonCallback(window, (Control::mouse_button_callback));

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.6, 0.6, 0.6, 1);
	initGame();
	//World* world = new World();
	//WorldInfo::world = World;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		Control::deltaTime = currentFrame - Control::lastFrame;
		Control::lastFrame = currentFrame;
		Control::processInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 960.0f);
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		WorldInfo::projection = projection;
		WorldInfo::view = view;
		skyDome->StateChange(glm::vec3(0, 0, 0), glm::vec3(200, 200, 200), projection, view);
		skyDome->Render();
		//world->render();
		World::render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
