#pragma once
#include "Chunk.h"
#include <vector>
#include <map>
#include <unordered_map>
static class World
{
public:
	//World();
	//~World();
	static void render();
	static void update();
	static Chunk* getChunkByID(string id);
private:	
	//map<vector<int>, Chunk*> chunks;
	static unordered_map<string, Chunk*> hashChunkMap;
	static map<float, Block*> transBlock;

	static bool ifUpdate();
	static bool first;
	static void genChunk();
};

