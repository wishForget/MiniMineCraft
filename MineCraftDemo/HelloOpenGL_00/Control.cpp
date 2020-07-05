#include "Control.h"
#include <iostream>
#include "WorldInfo.h"
#include "Chunk.h"
#include "World.h"
#include "BlockUtil.h"
#include "CoordUtil.h"
#include "AABB.h"
#include "Ray.h"
#include "LandCoverGenerator.h"
#include <cmath>
using namespace std;

Camera* Control::camera = new Camera();
int Control::SCR_WIDTH = 1600, Control::SCR_HEIGHT = 800;
bool Control::debug = false;
float Control::lastX = SCR_WIDTH / 2.0f;
float Control::lastY = SCR_HEIGHT / 2.0f;
bool Control::firstMouse = true;
float Control::deltaTime = 0.0f;
float Control::lastFrame = 0.0f;
float Control::xpos = 0.0f;
float Control::ypos = 0.0f;
float Control::Myzpos = 0.0f;
float Control::Myypos = 0.0f;
float Control::Myxpos = 0.0f;
bool Control::mouseDown = false;

Control::Control()
{
}


Control::~Control()
{

}

void Control::init(int width, int height, Camera* _camera, bool ifDebug) {
	camera = _camera;
	SCR_WIDTH = width, SCR_HEIGHT = height;
	debug = ifDebug;
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
	firstMouse = true;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

void Control::buffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	cout << "cur window " << width << "  " << height << endl;
	Control::SCR_WIDTH = width;
	Control::SCR_HEIGHT = height;
}

void Control::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
	setCurMousePos(xpos, ypos);
}

void Control::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void Control::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	if (action == GLFW_PRESS) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		cout << "Mosue left button clicked!" << endl;
		cout << xpos << " " << ypos << endl;
		cout << "当前所在chunk loc " << (int)(camera->Position.x / WorldInfo::chunkSize) << "  "
			<< (int)(camera->Position.z / WorldInfo::chunkSize) << endl;
		cout << "当前位置 " << camera->Position.x << " " <<
			camera->Position.y << " " << camera->Position.z << endl;

		pick();
		//		AroundChunk();
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		cout << "Mosue middle button clicked!" << endl;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		cout << "Mosue right button clicked!" << endl;

		//cout << xpos << " " << ypos << endl;
		cout << "当前所在chunk loc " << (int)(camera->Position.x / WorldInfo::chunkSize) << "  "
			<< (int)(camera->Position.z / WorldInfo::chunkSize) << endl;
		cout << "当前位置 " << camera->Position.x << " " <<
			camera->Position.y << " " << camera->Position.z << endl;
		build();

		break;
	default:
		return;
	}
}

void Control::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->ProcessKeyboard(UPWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWNWARD, deltaTime);
	if (debug) {
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			std::cout << "当前位置： " << camera->Position.x << " " << camera->Position.y << " " << camera->Position.z << " " << std::endl;
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
			camera->Position = glm::vec3(0, 10, 0);
	}
}

void Control::setCurMousePos(float _xpos, float _ypos) {
	xpos = _xpos;
	ypos = Control::SCR_HEIGHT - _ypos;
}

int Control::DetectRayPolygon(glm::vec3 startPoint, glm::vec3 inAABBPoint, glm::vec3 testDir, glm::vec3 border) {
	//cout << "startPoint x y z " << startPoint.x << " " << startPoint.y << " " << startPoint.z << "\n";
	//cout << "innerPoint x y z " << inAABBPoint.x << " " << inAABBPoint.y << " " << inAABBPoint.z << "\n";
	//cout << "border x y z " << border.x << " " << border.y << " " << border.z << "\n";
	//cout << "testDir x y z " << testDir.x << " " << testDir.y << " " << testDir.z << "\n";
	bool polygon[6];
	for (int i = 0; i < 6; i++) {
		polygon[i] = true;
	}
	//射点
	float x = startPoint.x;
	float y = startPoint.y;
	float z = startPoint.z;

	//边缘点，也叫面上点
	float minx = border.x - 0.5;
	float miny = border.y - 0.5;
	float minz = border.z - 0.5;

	float maxx = border.x + 0.5;
	float maxy = border.y + 0.5;
	float maxz = border.z + 0.5;

	//到达面,面上的点检测
	float x0 = maxx;
	float y0 = maxy;
	float z0 = maxz;
	//x的判断
	if (x <= minx) {
		polygon[3] = false;
		x0 = minx;
	}
	else if (x >= maxx) {
		polygon[2] = false;
	}
	else if (x < maxx && x > minx)
	{
		polygon[3] = false;
		polygon[2] = false;

	}
	//y的判断
	if (y <= miny) {
		polygon[1] = false;
		y0 = miny;
	}
	else if (y >= maxy) {
		polygon[0] = false;
	}
	else if (y <= maxy && y >= miny)
	{
		polygon[0] = false;
		polygon[1] = false;

	}

	//z的判断
	if (z <= minz) {
		polygon[4] = false;
		z0 = minz;
	}
	else if (z >= maxz) {
		polygon[5] = false;
	}
	else if (z <= maxz && z >= minz)
	{
		polygon[4] = false;
		polygon[5] = false;

	}

	int count = 0;
	vector<int>contactPoly;
	bool polygonx = false, polygony = false, polygonz = false;

	//自由度的判断
	for (int i = 0; i < 6; i++) {
		if (polygon[i] == true) {
			count++;
			contactPoly.push_back(i);
			if (i == 0 || i == 1) {
				polygony = true;
			}
			if (i == 2 || i == 3) {
				polygonx = true;
			}
			if (i == 4 || i == 5) {
				polygonz = true;
			}
		}
	}

	//更快的到达 路程/斜率
	float xstep, ystep, zstep;
	xstep = abs((x - x0) / testDir.x);  // (x - Inx)是斜率
	ystep = abs((y - y0) / testDir.y);
	zstep = abs((z - z0) / testDir.z);


	if (count == 1) return contactPoly[0];
	if (count == 2) {
		if (polygonx == false) {
			if (ystep > zstep) return polygon[0] == true ? 0 : 1;
			else
			{
				return polygon[4] == true ? 4 : 5;
			}
		}
		else if (polygony == false) {
			if (xstep > zstep) return polygon[2] == true ? 2 : 3;
			else
			{
				return polygon[4] == true ? 4 : 5;
			}
		}
		else if (polygonz == false) {
			if (xstep > ystep) return polygon[2] == true ? 2 : 3;
			else
			{
				return polygon[0] == true ? 0 : 1;
			}
		}
	}
	else {
		if (xstep > ystep && xstep > zstep) {
			return polygon[2] == true ? 2 : 3;
		}
		else if (ystep > xstep &&ystep > zstep) {
			return polygon[0] == true ? 1 : 0;
		}
		else if (zstep > xstep &&zstep > ystep) {
			return polygon[4] == true ? 4 : 5;
		}
	}

	return 0;

}

void Control::build()
{
	//
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::vec3 res = glm::unProject(glm::vec3(xpos, ypos, 0), WorldInfo::view, WorldInfo::projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));
	glm::vec3 res1 = glm::unProject(glm::vec3(xpos, ypos, 1), WorldInfo::view, WorldInfo::projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));

	glm::vec3 testDir = glm::normalize(res1 - res);
	Ray* ray = new Ray(res, testDir, WorldInfo::rayTestStep, WorldInfo::rayTestStepNum);

	//nearOut = ray->next();
	while (ray->hasNext()) {
		glm::vec3 testPoint = ray->next();

		int _x = 0, _y = 0, _z = 0;
		CoordUtil::world2Chunk(Point3(testPoint.x, 0, testPoint.z), _x, _y, _z);
		Chunk* chunk = World::getChunkByID(BlockUtil::IDBuilder(_x, _y, _z));

		if (chunk == nullptr) {
			return;
		}

		unordered_map<string, Block*>::iterator iter;
		unordered_map<string, Block*> blockMap = chunk->getBlockMap();

		for (iter = blockMap.begin(); iter != blockMap.end(); iter++) {
			glm::mat4 modelTrans = iter->second->getTransModel();
			AABB aabb(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, 0.5), modelTrans);
			if (aabb.containPoint(testPoint)) {
				//点击的block的x,y,z
				int x = iter->second->getBlockX();
				int y = iter->second->getBlockY();
				int z = iter->second->getBlockZ();

				glm::vec3 nearOut = glm::vec3(camera->Position.x, camera->Position.y, camera->Position.z);
				int polyId = DetectRayPolygon(nearOut, testPoint, testDir, glm::vec3(x, y, z));
				string GenId;// = BlockUtil::IDBuilder(_x, _y, _z); 先要检查
				Point3 GenPoint;
				if (polyId == 0) {
					GenId = BlockUtil::IDBuilder(x, y + 1, z);
					GenPoint = Point3(x, y + 1, z);
				}
				else if (polyId == 1) {
					GenId = BlockUtil::IDBuilder(x, y - 1, z);
					GenPoint = Point3(x, y - 1, z);
				}
				else if (polyId == 2) {
					GenId = BlockUtil::IDBuilder(x - 1, y, z);
					GenPoint = Point3(x - 1, y, z);
				}
				else if (polyId == 3) {
					GenId = BlockUtil::IDBuilder(x + 1, y, z);
					GenPoint = Point3(x + 1, y, z);
				}
				else if (polyId == 4) {
					GenId = BlockUtil::IDBuilder(x, y, z + 1);
					GenPoint = Point3(x, y, z + 1);
				}
				else if (polyId == 5) {
					GenId = BlockUtil::IDBuilder(x, y, z - 1);
					GenPoint = Point3(x, y, z - 1);
				}

				unordered_map<string, Block*>::iterator finder;
				finder = blockMap.find(GenId);
				if (finder == blockMap.end()) {
					LandCoverGenerator::singleGenerator(chunk, GenPoint);

					//得到当前chunk的block的loc
					BlockUtil::setVisible(chunk, iter->second);
					return;
				}

			}
		}
	}
}



void Control::pick()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::vec3 res = glm::unProject(glm::vec3(xpos, ypos, 0), WorldInfo::view, WorldInfo::projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));
	glm::vec3 res1 = glm::unProject(glm::vec3(xpos, ypos, 1), WorldInfo::view, WorldInfo::projection, glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));

	glm::vec3 testDir = glm::normalize(res1 - res);
	Ray* ray = new Ray(res, testDir, WorldInfo::rayTestStep, WorldInfo::rayTestStepNum);
	while (ray->hasNext()) {
		glm::vec3 testPoint = ray->next();
		int _x = 0, _y = 0, _z = 0;
		CoordUtil::world2Chunk(Point3(testPoint.x, 0, testPoint.z), _x, _y, _z);
		Chunk* chunk = World::getChunkByID(BlockUtil::IDBuilder(_x, _y, _z));

		if (chunk == nullptr) {
			cout << "chunk: " << _x << "  " << _z << "不存在" << endl;
			return;
		}
		unordered_map<string, Block*>::iterator iter;
		unordered_map<string, Block*> blockMap = chunk->getBlockMap();

		for (iter = blockMap.begin(); iter != blockMap.end(); iter++) {
			glm::mat4 modelTrans = iter->second->getTransModel();
			AABB aabb(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, 0.5), modelTrans);
			if (aabb.containPoint(testPoint)) {

				//点击的block的x,y,z
				int x = iter->second->getBlockX();
				int y = iter->second->getBlockY();
				int z = iter->second->getBlockZ();
				unordered_map<string, Block*>::iterator finder;
				finder = blockMap.find(BlockUtil::IDBuilder(x, (y - 1), z));
				if (finder == blockMap.end()) {
					LandCoverGenerator::singleGenerator(chunk, Point3(x, (y - 1), z));
				}

				//string newId = BlockUtil::IDBuilder(testPoint.x, testPoint.y - 1, testPoint.z);会有差别
				string newId = BlockUtil::IDBuilder(x, (y - 1), z);
				if (chunk->showBlock(newId)) {
					cout << "创建的new Chunk是" << newId << ",已存在\n";
				}
				else
				{
					cout << "ERROR";
				}
				Point2 front = Point2(x, z + 1);
				int f = (int)chunk->getHeightAt(front);
				Point2 back = Point2(x, z - 1);
				int b = (int)chunk->getHeightAt(back);
				Point2 left = Point2(x - 1, z);
				int l = (int)chunk->getHeightAt(left);
				Point2 right = Point2(x + 1, z);
				int r = (int)chunk->getHeightAt(right);
				int center = (int)chunk->getHeightAt(Point2(x, z));
				int height[4] = { f,b,l,r };
				Point2 p[4] = { front,back,left,right };
				for (int i = 0; i <= 3; i++) {
					unordered_map<string, Block*>::iterator finder;
					finder = blockMap.find(BlockUtil::IDBuilder(p[i].x, y, p[i].y));
					if (finder == blockMap.end()) {
						if (y < height[i]) {
							LandCoverGenerator::singleGenerator(chunk, Point3(p[i].x, y, p[i].y));
						}
					}
				}
				chunk->erase(iter->first);
				//我要得到当前chunk的block的loc
				BlockUtil::setVisible(chunk, iter->second);
				return;
			}
		}
	}
}
		

