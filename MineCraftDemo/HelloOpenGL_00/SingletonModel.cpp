#include "SingletonModel.h"
#include "BlockUtil.h"
Model * SingletonModel::grassModel = nullptr;
Model * SingletonModel::soilModel = nullptr;
Model * SingletonModel::sandModel = nullptr;
Model * SingletonModel::glassModel = nullptr;
Model * SingletonModel::snowModel = nullptr;
Model * SingletonModel::dandelion = nullptr;
Model* SingletonModel::sunflower = nullptr;
Model* SingletonModel::winterJasmine = nullptr;
Model* SingletonModel::tulip = nullptr;
Model* SingletonModel::rose = nullptr;
Model* SingletonModel::tallGrass = nullptr;
Model* SingletonModel::stoneModel = nullptr;
Model* SingletonModel::waterModel = nullptr;

Model * SingletonModel::getGrassModel()
{
	if (!grassModel) {
		vector<Point2> points;
		points.push_back(Point2(0.0, 15.0)); //前
		points.push_back(Point2(0.0, 15.0)); //后
		points.push_back(Point2(0.0, 15.0)); //左
		points.push_back(Point2(0.0, 15.0)); //右
		points.push_back(Point2(0.0, 14.0)); //上
		points.push_back(Point2(0.0, 16.0)); //下
		float texLoc[72];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		grassModel = new Model(36);
		grassModel->init(texLoc);
	}
	return grassModel;
}

Model * SingletonModel::getSoilModel()
{
	if (!soilModel) {
		vector<Point2> points;
		points.push_back(Point2(6.0, 16.0)); //前
		points.push_back(Point2(6.0, 16.0)); //后
		points.push_back(Point2(6.0, 16.0)); //左
		points.push_back(Point2(6.0, 16.0)); //右
		points.push_back(Point2(6.0, 16.0)); //上
		points.push_back(Point2(6.0, 16.0)); //下
		float texLoc[72];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		soilModel = new Model(36);
		soilModel->init(texLoc);
	}
	
	return soilModel;
}

Model * SingletonModel::getSandModel()
{
	if (!sandModel) {
		vector<Point2> points;
		points.push_back(Point2(1.0, 16.0)); //前
		points.push_back(Point2(1.0, 16.0)); //后
		points.push_back(Point2(1.0, 16.0)); //左
		points.push_back(Point2(1.0, 16.0)); //右
		points.push_back(Point2(1.0, 16.0)); //上
		points.push_back(Point2(1.0, 16.0)); //下
		float texLoc[72];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		sandModel = new Model(36);
		sandModel->init(texLoc);
	}

	return sandModel;
}

Model * SingletonModel::getGlassModel()
{
	if (!glassModel) {
		vector<Point2> points;
		points.push_back(Point2(9.0, 16.0)); //前
		points.push_back(Point2(9.0, 16.0)); //后
		points.push_back(Point2(9.0, 16.0)); //左
		points.push_back(Point2(9.0, 16.0)); //右
		points.push_back(Point2(9.0, 16.0)); //上
		points.push_back(Point2(9.0, 16.0)); //下
		float texLoc[72];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		glassModel = new Model(36);
		glassModel->init(texLoc);
	}

	return glassModel;
}

Model * SingletonModel::getDandelionModel()
{
	if (!dandelion) {
		vector<Point2> points;
		points.push_back(Point2(1.0, 13.0)); //前
		points.push_back(Point2(1.0, 13.0)); //后
		float texLoc[24];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		dandelion = new Model(12);
		dandelion->init(texLoc);
	}
	return dandelion;
}

Model * SingletonModel::getSnowModel()
{
	if (!snowModel) {
		vector<Point2> points;
		points.push_back(Point2(8.0, 15.0)); //前
		points.push_back(Point2(8.0, 15.0)); //后
		points.push_back(Point2(8.0, 15.0)); //左
		points.push_back(Point2(8.0, 15.0)); //右
		points.push_back(Point2(8.0, 14.0)); //上
		points.push_back(Point2(8.0, 16.0)); //下
		float texLoc[72];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		snowModel = new Model(36);
		snowModel->init(texLoc);
	}
	return snowModel;
}

Model * SingletonModel::getSunflowerModel()
{
	if (!sunflower) {
		vector<Point2> points;
		points.push_back(Point2(4.0, 13.0)); //前
		points.push_back(Point2(4.0, 13.0)); //后
		float texLoc[24];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		sunflower = new Model(12);
		sunflower->init(texLoc);
	}
	return sunflower;
}

Model * SingletonModel::getWinterJasmineModel()
{
	if (!winterJasmine) {
		vector<Point2> points;
		points.push_back(Point2(5.0, 13.0)); //前
		points.push_back(Point2(5.0, 13.0)); //后
		float texLoc[24];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		winterJasmine = new Model(12);
		winterJasmine->init(texLoc);
	}
	return winterJasmine;
}

Model * SingletonModel::getTulipModel()
{
	if (!tulip) {
		vector<Point2> points;
		points.push_back(Point2(3.0, 13.0)); //前
		points.push_back(Point2(3.0, 13.0)); //后
		float texLoc[24];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		tulip = new Model(12);
		tulip->init(texLoc);
	}
	return tulip;
}

Model * SingletonModel::getRoseModel()
{
	if (!rose) {
		vector<Point2> points;
		points.push_back(Point2(2.0, 13.0)); //前
		points.push_back(Point2(2.0, 13.0)); //后
		float texLoc[24];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		rose = new Model(12);
		rose->init(texLoc);
	}
	return rose;
}

Model * SingletonModel::getTallGrass()
{
	if (!tallGrass) {
		vector<Point2> points;
		points.push_back(Point2(2.0, 13.0)); //前
		points.push_back(Point2(2.0, 13.0)); //后
		float texLoc[24];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		tallGrass = new Model(12);
		tallGrass->init(texLoc);
	}
	return tallGrass;
}

Model * SingletonModel::getStoneModel()
{
	if (!stoneModel) {
		vector<Point2> points;
		points.push_back(Point2(5.0, 16.0)); //前
		points.push_back(Point2(5.0, 16.0)); //后
		points.push_back(Point2(5.0, 16.0)); //左
		points.push_back(Point2(5.0, 16.0)); //右
		points.push_back(Point2(5.0, 16.0)); //上
		points.push_back(Point2(5.0, 16.0)); //下
		float texLoc[72];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		stoneModel = new Model(36);
		stoneModel->init(texLoc);
	}
	return stoneModel;
}

Model * SingletonModel::getWaterModel()
{
	if (!waterModel) {
		vector<Point2> points;
		points.push_back(Point2(9.0, 4.0)); //上
		float texLoc[12];
		BlockUtil::imgCoord2textureCoord(points, texLoc);
		waterModel = new Model(6);
		waterModel->init(texLoc);
	}
	return waterModel;
}

SingletonModel::SingletonModel()
{
}

