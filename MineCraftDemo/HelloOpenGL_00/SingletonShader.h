#pragma once
#include "learnopengl/shader.h"
class SingletonShader
{
public:
	static Shader* getSimpleShader();
	static Shader* getSkyDomeShader();
	static Shader* getLightShader();
	static Shader* getTransparentShader();
private:
	SingletonShader();
	//~SingletonShader();
	static Shader *simpleShader;// = nullptr;
	static Shader *skyDomShader;
	static Shader *transparentShader;// = nullptr;
	static Shader *lightShader; //´ø¹âÕÕµÄshader
	static Shader *otherShader;// = nullptr;
};

