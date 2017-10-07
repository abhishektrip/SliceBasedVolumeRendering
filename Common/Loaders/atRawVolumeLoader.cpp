#include "atRawVolumeLoader.h"
#include "atCubicSpline.h"
using namespace atRenderEngine;


atRawVolumeLoader::atRawVolumeLoader()
{
}

atRenderEngine::atRawVolumeLoader::atRawVolumeLoader(string filename)
{

}


atRawVolumeLoader::~atRawVolumeLoader()
{
	if (mFileHandle.is_open())
	{
		mFileHandle.close();
	}
}

void atRenderEngine::atRawVolumeLoader::LoadFile(string filename, int height, int width, int depth, char *& buffer, vector<Vector4f>& transferFunction, vector<Utility::TransferFunction1DPoint> colorPoints, vector<Utility::TransferFunction1DPoint> alphaPoints)
{
	if (!mFileHandle.is_open())
	{
		LoadFileInternal(filename, height*width*depth, buffer);		
		ComputeTransferFunction(transferFunction, colorPoints, alphaPoints);
	}
}

void atRenderEngine::atRawVolumeLoader::LoadFile(string filename, char *& buffer)
{
	if (!mFileHandle.is_open())
	{
		LoadFileInternal(filename, FILE_SIZE_UNKNOWN, buffer);
	}
}

void atRenderEngine::atRawVolumeLoader::LoadFileInternal(string filename, const int bufferSize, char* &buffer)
{
	streampos size;
	std::string ext = ".pvm";
	std::size_t found = filename.find(ext);
	mFileHandle.open(filename, ios::in | ios::binary | ios::ate);
	if (mFileHandle.is_open())
	{	
		//raw file
		size = mFileHandle.tellg();
		const int bSize = (size > bufferSize && bufferSize != FILE_SIZE_UNKNOWN) ? bufferSize : size;
		buffer = new char[bSize];
		mFileHandle.seekg(0, mFileHandle.beg);
		mFileHandle.read(buffer, bSize);
		mFileHandle.close();
	}
}

void atRenderEngine::atRawVolumeLoader::ComputeTransferFunction(vector<Vector4f>& transferFunction, vector<Utility::TransferFunction1DPoint> colorPoints, vector<Utility::TransferFunction1DPoint> alphaPoints)
{
	//initialize the cubic spline for the transfer function
	transferFunction.resize(256);

	auto colorCubic = Utility::CalculateCubicSpline(colorPoints.size() - 1, colorPoints);
	auto alphaCubic = Utility::CalculateCubicSpline(alphaPoints.size() - 1, alphaPoints);

	int numTF = 0;
	for (int i = 0; i < colorPoints.size() - 1; i++)
	{
		int steps = colorPoints[i + 1].sampleValue - colorPoints[i].sampleValue;

		for (int j = 0; j < steps; j++)
		{
			float k = (float)j / (float)(steps - 1);

			transferFunction[numTF++] = colorCubic[i].GetPointOnSpline(k);
		}
	}

	numTF = 0;
	for (int i = 0; i < alphaPoints.size() - 1; i++)
	{
		int steps = alphaPoints[i + 1].sampleValue - alphaPoints[i].sampleValue;

		for (int j = 0; j < steps; j++)
		{
			float k = (float)j / (float)(steps - 1);

			transferFunction[numTF++].w() = alphaCubic[i].GetPointOnSpline(k).w();
		}
	}
}
