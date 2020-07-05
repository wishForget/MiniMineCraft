#pragma once
#include "Model.h"
class SingletonModel
{
public:
	static Model* getGrassModel(); //²Ý
	static Model* getSoilModel();   //ÍÁ
	static Model* getSandModel();  //É³
	static Model* getGlassModel(); //²£Á§
	static Model* getDandelionModel(); //»¨
	static Model* getSnowModel(); //Ñ©
	static Model* getSunflowerModel();
	static Model* getWinterJasmineModel();
	static Model* getTulipModel();
	static Model* getRoseModel();
	static Model* getTallGrass();
	static Model* getStoneModel();
	static Model* getWaterModel();
private:
	SingletonModel();
	static Model* grassModel;
	static Model* soilModel;
	static Model* sandModel;
	static Model* glassModel;
	static Model* dandelion; //ÆÑ¹«Ó¢
	static Model* snowModel;
	static Model* sunflower;  //ÏòÈÕ¿û
	static Model* winterJasmine;  //Ó­´º»¨
	static Model* tulip;  //Óô½ðÏã
	static Model* rose; //Ãµ¹å
	static Model* tallGrass; //²Ý£¨Ö²Îï£©
	static Model* stoneModel;
	static Model* waterModel;

};

