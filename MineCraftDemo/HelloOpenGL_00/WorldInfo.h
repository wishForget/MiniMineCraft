#pragma once
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <queue>
#include "Point.h"
#include <thread>
#include <future>
class World;
using namespace std;
struct ChunkGenTask {
	float dis;
	Point3 point;
	ChunkGenTask(float _dis, Point3 _point) : dis(_dis), point(_point) {}
	bool operator < (ChunkGenTask const &a) const {
		return dis > a.dis;
	}
};

class WorldInfo
{
public:
	WorldInfo();
	~WorldInfo();
	//static std::thread t;
	static priority_queue<ChunkGenTask> chunkGenTaskPriorityQueue;
	//渲染参数
	static bool useLight; //使用光照明
	static bool useFog; //使用雾化效果
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 lastUpdatePostion;  //上次更新chunk时所在位置
	static float maxUpdateIntervalDis; //移动了多大的距离便要更新了
	static float renderRadius;  //渲染距离
	static int renderChunkRadius;  //
	static int chunkSize; //每个chunk中长宽有多少个block
	static int chunkHeight;
	//光照参数
	static glm::vec3 lightPos;
	static glm::vec3 ambient;
	static glm::vec3 diffuse;
	static glm::vec3 specular;
	//雾参数
	static float fogMaxDist;
	static float fogMinDist;
	static glm::vec4 fogColor;
	//水参数
	static float waterLevel;  //水平面
	static glm::vec4 WorldInfo::waterColor;
	static float waterViewMaxDist;  //在水中最远可见
	//static float fogMinDist;
	//射线检测（拾取参数）
	static float rayTestDis;  //射线检测总长度
	static float rayTestStep;  //射线检测的精度
	static int rayTestStepNum;  //射线检测的步数
	//static glm::vec3 cameraPos;
	static World* world;
};


