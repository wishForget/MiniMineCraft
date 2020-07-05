#pragma once
#include <vector>
#include <map>
#include <unordered_map>
//#include <unordered_map>
#include "Block.h"
using namespace std;
class Chunk
{
public:
	Chunk();
	Chunk(int x, int z);
	~Chunk();
	void render();
	void setLoc(int x, int z);
	Point3* getLoc();
	Point3* getCenterLoc();
	unordered_map<string, Block*>* getBlockMapAddress();
	unordered_map<string, Block*> getBlockMap();
	unordered_map<string, Block*> getTransparentBlockMap();
	unordered_map<string, Block*>* getTransparentBlockMapAddress();

	Block* getBlockAt(Point3 point);
	Block* getHeadBlockAt(Point3 point);
	Block* getTopBlockAt(Point2 point);  //获取x, z位置的顶部元素
	
	int getHeightAt(Point2 point);
	void setMinHeight(int height);
	void setMaxHeight(int height);
	int getMinHeight();
	int getMaxHeight();

	bool erase(string id);  //擦除方块
	bool showBlock(string id); //显示方块
	bool hidenBlock(string id); //隐藏方块
	bool addBlock(int type, Point3 loc);

	map<vector<int>, float> heightMap; //键为{x,z}，值为h
private:
	unordered_map<string, Block*> blockMap;  //不带透明色的block
	unordered_map<string, Block*> transparentBlockMap;  //带透明色的block
	Point3* loc = new Point3(0, 0, 0); //chunk在chunk坐标系下的左上角（x,z)坐标
	Point3* centerLoc = new Point3(8, 0, 8);  //

	int minHeight = 0;
	int maxHeight = 0;

	glm::vec3 scale;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::vec3 lightPos;
	glm::vec3 cameraPos;
};

