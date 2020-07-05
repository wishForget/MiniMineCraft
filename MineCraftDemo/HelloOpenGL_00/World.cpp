#include "World.h"
#include "WorldInfo.h"
#include "Control.h"
#include "BlockUtil.h"
#include "CoordUtil.h"
#include <thread>
#include <future>

//World::World()
//{
//	update();
//}
//
//
//World::~World()
//{
//}
bool World::first = true;
unordered_map<string, Chunk*> World::hashChunkMap = unordered_map<string, Chunk*>();
map<float, Block*> World::transBlock = map<float, Block*>();

void World::render()
{
	unordered_map<string, Block*>::iterator blockIter;
	unordered_map<string, Block*> curChunkTransMap;
	Point3* loc;
	for (unordered_map<string, Chunk*>::iterator iter = hashChunkMap.begin(); iter != hashChunkMap.end(); iter++) {
		if (!BlockUtil::ifRender(iter->second)) {
			continue;
		}
		iter->second->render();

		curChunkTransMap = iter->second->getTransparentBlockMap();
		for (blockIter = curChunkTransMap.begin(); blockIter != curChunkTransMap.end(); blockIter++) {
			loc = blockIter->second->getBlockData()->getLoc();
			float dis = glm::length(Control::camera->Position - glm::vec3(loc->x, loc->y, loc->z));
			transBlock[dis] = blockIter->second;
		}
	}
	for (map<float, Block*>::reverse_iterator sortIter = transBlock.rbegin(); sortIter != transBlock.rend(); sortIter++) {
		Point3* p = sortIter->second->getBlockData()->getLoc();
		glm::vec3 cameraPos = Control::camera->Position;
		if (glm::length(glm::vec3(p->x, 0, p->z) - glm::vec3(cameraPos.x, 0, cameraPos.z)) > WorldInfo::renderRadius) {
			continue;
		}
		sortIter->second->stateChange(WorldInfo::projection, WorldInfo::view, glm::vec3(1.0f), glm::vec3(1.0f));
		sortIter->second->render();
	}
	transBlock.clear();
	update();
}

void World::update()
{
	if (!WorldInfo::chunkGenTaskPriorityQueue.empty()){
		//std::thread t(genChunk);
		//t.join();
		//t.detach();
		genChunk();
	}
	if (!ifUpdate()) {
		return;
	}
	int curChunkLocX;
	int curChunkLocZ;
	int y;
	CoordUtil::world2Chunk(Point3(Control::camera->Position.x, 0, Control::camera->Position.z), curChunkLocX, y, curChunkLocZ);
	

	int stepNum = (int)(WorldInfo::renderRadius / WorldInfo::chunkSize);

	for (int x = curChunkLocX - stepNum; x < curChunkLocX + stepNum; x++) {
		for (int z = curChunkLocZ - stepNum; z < curChunkLocZ + stepNum; z++) {
			string id = BlockUtil::IDBuilder(x, 0, z);
			if (0 == hashChunkMap.count(id)) {
				float dis = glm::length(glm::vec3(x + 0.5*WorldInfo::chunkSize, 0, z + 0.5*WorldInfo::chunkSize) - glm::vec3(Control::camera->Position.x, 0, Control::camera->Position.z));
				ChunkGenTask task(dis, Point3(x, 0, z));
				WorldInfo::chunkGenTaskPriorityQueue.push(task);
			}
		}
	}
}

Chunk* World::getChunkByID(string id)
{
	unordered_map<string, Chunk*>::iterator chunkFinder;
	chunkFinder = hashChunkMap.find(id);
	if (chunkFinder != hashChunkMap.end()) {
		return (chunkFinder->second);
	}
	return nullptr;
}

bool World::ifUpdate()
{
	float dis = glm::length(WorldInfo::lastUpdatePostion - Control::camera->Position);
	if (first ||  (dis >= WorldInfo::maxUpdateIntervalDis)) {
		first = false;
		WorldInfo::lastUpdatePostion = Control::camera->Position;
		return true;
	}
	return false;
}

void World::genChunk()
{
	ChunkGenTask task = WorldInfo::chunkGenTaskPriorityQueue.top();
	Point3 newTask = task.point;
	Chunk* chunk = new Chunk(newTask.x, newTask.z);
	string id = BlockUtil::IDBuilder(newTask.x, 0, newTask.z);
	hashChunkMap[id] = chunk;
	WorldInfo::chunkGenTaskPriorityQueue.pop();
}
