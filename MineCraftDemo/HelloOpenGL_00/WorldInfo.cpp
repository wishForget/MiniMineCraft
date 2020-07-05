#include "WorldInfo.h"
#include "World.h"
glm::mat4 WorldInfo::projection = glm::mat4(1.0f);
glm::mat4 WorldInfo::view = glm::mat4(1.0f);

glm::vec3 WorldInfo::lastUpdatePostion = glm::vec3(0, 0, 0);
priority_queue<ChunkGenTask> WorldInfo::chunkGenTaskPriorityQueue = priority_queue<ChunkGenTask>();
int WorldInfo::chunkSize = 16;
int WorldInfo::chunkHeight = 128;
int WorldInfo::renderChunkRadius = 2;
float WorldInfo::renderRadius = WorldInfo::renderChunkRadius*WorldInfo::chunkSize;
float WorldInfo::maxUpdateIntervalDis = 0.1*WorldInfo::renderRadius;

bool WorldInfo::useLight = true;
bool WorldInfo::useFog = true;

glm::vec3 WorldInfo::lightPos = glm::vec3(10.0f, 30.0f, 7.0f);

glm::vec3 WorldInfo::ambient = glm::vec3(0.7f, 0.7f, 0.7f);
glm::vec3 WorldInfo::diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
glm::vec3 WorldInfo::specular = glm::vec3(0.1f, 0.1f, 0.1f);
//ŒÌ‰÷»æ
float WorldInfo::fogMinDist = 0.7*WorldInfo::renderRadius;
float WorldInfo::fogMaxDist = 1*WorldInfo::renderRadius;
glm::vec4 WorldInfo::fogColor = glm::vec4(0.6, 0.6, 0.6, 1);
//ÀÆ‰÷»æ
float WorldInfo::waterLevel = 11.5;
glm::vec4 WorldInfo::waterColor = glm::vec4(92, 110, 220, 1);
float WorldInfo::waterViewMaxDist = 15.0f;
//waterViewMaxDist
//92, 110, 220
World* WorldInfo::world = nullptr;
int WorldInfo::rayTestStepNum = 20;
float WorldInfo::rayTestStep = 0.25;
float WorldInfo::rayTestDis = WorldInfo::rayTestStepNum*WorldInfo::rayTestStep;
WorldInfo::WorldInfo()
{
}


WorldInfo::~WorldInfo()
{
}
