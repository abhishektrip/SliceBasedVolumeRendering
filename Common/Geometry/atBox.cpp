#include "atBox.h"
using namespace atRenderEngine;


atBox::atBox():mColor(Vector3f(1,0,0))
{
	// Create a unit 3d cube
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles.

	const int CUBE_FACES = 6;
	const int CUBE_TRIANGLES = CUBE_FACES * 2;
	const int VERTICES_PER_TRIANGLE = 3;
	const int UNIQUE_VERTICES_PER_CUBE = 8;

	mVertexList = std::vector<Eigen::Vector3f>({
		Eigen::Vector3f(-1.0f, -1.0f, 1.0f),
		Eigen::Vector3f(1.0f, -1.0f, 1.0f),
		Eigen::Vector3f(-1.0f, 1.0f, 1.0f),
		Eigen::Vector3f(1.0f, 1.0f, 1.0f),
		Eigen::Vector3f(-1.0f, -1.0f, -1.0f),
		Eigen::Vector3f(1.0f, -1.0f, -1.0f),
		Eigen::Vector3f(-1.0f, 1.0f, -1.0f),
		Eigen::Vector3f(1.0f, 1.0f, -1.0f),


		//Eigen::Vector3f(0.0, 0.0, 0.0),
		//Eigen::Vector3f(0.0, 0.0, 1.0),
		//Eigen::Vector3f(0.0, 1.0, 0.0),
		//Eigen::Vector3f(0.0, 1.0, 1.0),
		//Eigen::Vector3f(1.0, 0.0, 0.0),
		//Eigen::Vector3f(1.0, 0.0, 1.0),
		//Eigen::Vector3f(1.0, 1.0, 0.0),
		//Eigen::Vector3f(1.0, 1.0, 1.0)
	});

	mEdgeList = std::vector<Vector2i>({
		Vector2i(0,2),
		Vector2i(2,3),
		Vector2i(3,1),
		Vector2i(1,0),
		Vector2i(2,6),
		Vector2i(3,7),
		Vector2i(0,4),
		Vector2i(1,5),
		Vector2i(4,6),
		Vector2i(6,7),
		Vector2i(7,5),
		Vector2i(5,4),
	});
	//ReadObjFile("../Common/StandardShapes/Cube.obj");
}


atBox::~atBox()
{
}

void atRenderEngine::atBox::FindMinMax(Utility::MinMaxPair & result)
{
	result.minValue = std::numeric_limits<float>::max();
	result.maxValue = std::numeric_limits<float>::min();
	for each (auto vertex in mVertexList)
	{
		
		if (vertex.z() < result.minValue)
		{
			result.minValue = vertex.z();
		}
		if (vertex.z() > result.maxValue)
		{
			result.maxValue = vertex.z();
		}
	}
}
void atBox::SetYRotation(float degree)
{	
	mRotationInY = degree;
	mRotationMatrix = Utility::eulerAngleYXZ(-mRotationInY, 0, 0);
}

std::vector<Vector3f> atRenderEngine::atBox::DrawableBoxVertices()
{
	std::vector<Vector3f> drawableVerts;

	for each (auto edge in mEdgeList)
	{
		drawableVerts.push_back(mVertexList[edge.x()]);
		drawableVerts.push_back(mVertexList[edge.y()]);
	}
	return drawableVerts;
}

std::vector<Vector3f> atRenderEngine::atBox::DrawableBoxColors()
{
	return std::vector<Vector3f>(24, mColor);
}

