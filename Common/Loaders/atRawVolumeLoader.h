#pragma once
#include "atUtility.h"

using namespace std;
namespace atRenderEngine
{
#define FILE_SIZE_UNKNOWN -1
	class atRawVolumeLoader
	{
	public:
		atRawVolumeLoader();
		atRawVolumeLoader(string filename);

		~atRawVolumeLoader();
		void LoadFile(string filename, int height, int width, int depth, char* &buffer, vector<Vector4f>& transferFunction,vector<Utility::TransferFunction1DPoint> colorPoints, vector<Utility::TransferFunction1DPoint> alphaPoints);
		void LoadFile(string filename, char* &buffer);
		
	private:
		void LoadFileInternal(string filename, const int bufferSize, char* &buffer);
		void ComputeTransferFunction(vector<Vector4f>& transferFunction, vector<Utility::TransferFunction1DPoint> colorPoints, vector<Utility::TransferFunction1DPoint> alphaPoints);
		ifstream mFileHandle;
	};
}

