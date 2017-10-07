#include "atVolumeRenderingScene.h"
using namespace atRenderEngine;


atVolumeRenderingScene::atVolumeRenderingScene()
{
	atBox* volumeBoundingBox = new atBox();
	mMeshesInScene.push_back(volumeBoundingBox);
}


atVolumeRenderingScene::~atVolumeRenderingScene()
{
}

void atRenderEngine::atVolumeRenderingScene::LoadRawVolume(std::string path,
	unsigned int numberOfSlices,
	vector<Utility::TransferFunction1DPoint> colorPoints,
	vector<Utility::TransferFunction1DPoint> alphaPoints,
	unsigned int xRange,
	unsigned int yRange,
	unsigned int zRange)
{
	char* buffer;
	char* rgbaBuffer;
	vector<Vector4f> transferFunction(256, Vector4f::Ones());

	//Set volume bounding box to match the volume size. 
	atBox* volumeBoundingBox = (atBox*)mMeshesInScene[0];
	//volumeBoundingBox->SetTranslation(Vector3f(0.0, 0.5, 0.0));
	int maxDim = std::max(std::max(xRange, yRange), zRange);
	Vector3f volumeScale((float)xRange / (float)maxDim, (float)yRange / (float)maxDim, (float)xRange / (float)maxDim);
	volumeBoundingBox->SetScaling(volumeScale);



	//Utility::MinMaxPair boxMinMax;
	//volumeBoundingBox->FindMinMax(boxMinMax);
	
	mRawVolumeLoader.LoadFile(path, xRange, yRange, zRange, buffer,transferFunction,colorPoints,alphaPoints);
	
	//Utility::convertToRGBA(rgbaBuffer, buffer, xRange*yRange*zRange);

	//if (rgbaBuffer != nullptr)
	//{
	//	mVRShader.Setup(*quad, rgbaBuffer, xRange, yRange, zRange);
	//	mSlices = zRange;
	//}
	
	if (buffer != nullptr)
	{
		mVRShader.Setup(mSliceQuad, buffer,transferFunction, xRange, yRange, zRange);
		mSlices = numberOfSlices;
	}

	//if (buffer != nullptr)
	//{
	//	mVRShader.Setup(*volumeBoundingBox, buffer, xRange, yRange, zRange);
	//	mSlices = numberOfSlices;
	//}
	//delete[] rgbaBuffer;
	delete[] buffer;
	Setup();
}

void atVolumeRenderingScene::Setup()
{
	mProgramID = mVRShader.mProgramId;
}

void atVolumeRenderingScene::Draw(Matrix4f& viewMatrix, Matrix4f& projectionMatrix)
{
	atBox* box = (atBox*)mMeshesInScene[0];	
	Matrix4f VPMatrix = projectionMatrix * viewMatrix;
	Matrix4f MVPMatrix = VPMatrix * box->GetModel();

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Disable lighting
	glDisable(GL_LIGHTING);
	
	//Disable Depth Test
	glDisable(GL_DEPTH_TEST);
	glDepthMask(0);
	
	//lineShader.Draw(box->DrawableBoxVertices(), box->DrawableBoxColors(), MVPMatrix);
	mVRShader.Draw(mSliceQuad, mSlices, viewMatrix, projectionMatrix, box->GetModel());
	
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(1);

	
	//lineShader.DrawCoordinateAxes(VPMatrix);

}
