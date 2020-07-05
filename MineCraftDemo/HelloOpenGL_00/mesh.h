#ifndef MESH_H
#define	MESH_H

#include <map>
#include <vector>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "util.h"
#include "math_3d.h"
#include "texture.h"

using namespace std;

class Mesh
{
public:
	Mesh();

	~Mesh();

	bool LoadMesh(const string& Filename);

	void Render();

	unsigned int NumBones() const
	{
		return m_NumBones;
	}

	void BoneTransform(float TimeInSeconds, vector<Matrix4f>& Transforms);
	vector<Vector3f> GetVertexs();  // 获取顶点数组
	vector<unsigned int> GetTriangleIndexBase();  //获取三角形索引
private:
#define NUM_BONES_PER_VEREX 4
	vector<Vector3f> vertexs; //顶点数据
	vector<unsigned int> triangleIndexBase; // 三角形索引数组
	struct BoneInfo
	{
		Matrix4f BoneOffset;
		Matrix4f FinalTransformation;

		BoneInfo()
		{
			BoneOffset.SetZero();
			FinalTransformation.SetZero();
		}
	};

	struct VertexBoneData
	{
		unsigned int IDs[NUM_BONES_PER_VEREX];
		float Weights[NUM_BONES_PER_VEREX];

		VertexBoneData()
		{
			Reset();
		};

		void Reset()
		{
			ZERO_MEM(IDs);
			ZERO_MEM(Weights);
		}

		void AddBoneData(unsigned int BoneID, float Weight);
	};

	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
	void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform);
	bool InitFromScene(const aiScene* pScene, const string& Filename);
	void InitMesh(unsigned int MeshIndex,
		const aiMesh* paiMesh,
		vector<Vector3f>& Positions,
		vector<Vector3f>& Normals,
		vector<Vector2f>& TexCoords,
		vector<VertexBoneData>& Bones,
		vector<unsigned int>& Indices);
	void LoadBones(unsigned int MeshIndex, const aiMesh* paiMesh, vector<VertexBoneData>& Bones);
	bool InitMaterials(const aiScene* pScene, const string& Filename);
	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	enum VB_TYPES {
		INDEX_BUFFER,
		POS_VB,
		NORMAL_VB,
		TEXCOORD_VB,
		BONE_VB,
		NUM_VBs
	};

	GLuint m_VAO;
	GLuint m_Buffers[NUM_VBs];

	struct MeshEntry {
		MeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};

	vector<MeshEntry> m_Entries;
	vector<Texture*> m_Textures;

	map<string, unsigned int> m_BoneMapping; // maps a bone name to its index
	unsigned int m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	Matrix4f m_GlobalInverseTransform;

	const aiScene* m_pScene;
	Assimp::Importer m_Importer;
};


#endif	/* MESH_H */


