#include "atQuad.h"

using namespace atRenderEngine;

atQuad::atQuad()
{
	mVertexList = std::vector<Eigen::Vector3f>({
		Eigen::Vector3f(-1.0f, -1.0f, 0.0f),
		Eigen::Vector3f(1.0f, -1.0f, 0.0f),
		Eigen::Vector3f(1.0f, 1.0f, 0.0f),
		Eigen::Vector3f(-1.0f, 1.0f, 0.0f)
	});

	mUVList = std::vector<Eigen::Vector2f>({
		Eigen::Vector2f(0.0f, 0.0f),
		Eigen::Vector2f(1.0f, 0.0f),
		Eigen::Vector2f(1.0f, 1.0f),
		Eigen::Vector2f(0.0f, 1.0f)
	});
	
	mNormalList = std::vector<Eigen::Vector3f>({
		Eigen::Vector3f(0.0f,0.0f,1.0f),
		Eigen::Vector3f(0.0f,0.0f,1.0f),
		Eigen::Vector3f(0.0f,0.0f,1.0f),
		Eigen::Vector3f(0.0f,0.0f,1.0f),
	});

	//Triangle #1
	Utility::TriangleData triData1;
	triData1.vertexIdx[0] = triData1.normalIdx[0] = triData1.uvIdx[0] = 0;
	triData1.vertexIdx[1] = triData1.normalIdx[1] = triData1.uvIdx[1] = 1;
	triData1.vertexIdx[2] = triData1.normalIdx[2] = triData1.uvIdx[2] = 2;

	Utility::TriangleData triData2;
	triData2.vertexIdx[0] = triData2.normalIdx[0] = triData2.uvIdx[0] = 2;
	triData2.vertexIdx[1] = triData2.normalIdx[1] = triData2.uvIdx[1] = 3;
	triData2.vertexIdx[2] = triData2.normalIdx[2] = triData2.uvIdx[2] = 0;

	mTriangleList.push_back(triData1);
	mTriangleList.push_back(triData2);
}


atQuad::~atQuad()
{
}
