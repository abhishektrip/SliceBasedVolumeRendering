#pragma once
#include "atScene.h"
#include "atRawVolumeLoader.h"
#include "atVolumeRendererShader.h"
#include "atQuad.h"
#include "atLineShader.h"

namespace atRenderEngine
{
	class atVolumeRenderingScene :
		public atScene
	{
	public:
		atVolumeRenderingScene();
		~atVolumeRenderingScene();
		void Setup() override;
		void Draw(Matrix4f & viewMatrix, Matrix4f & projectionMatrix) override;
		void LoadRawVolume(std::string path,
						unsigned int numberOfSlices,
						vector<Utility::TransferFunction1DPoint> colorPoints,
						vector<Utility::TransferFunction1DPoint> alphaPoints,
						unsigned int xRange = 0,
						unsigned int yRange = 0,
						unsigned int zRange = 0);
	private:
		atRawVolumeLoader mRawVolumeLoader; 
		Utility::atVolumeRenderingShader mVRShader;
		int mSlices;		
		atQuad mSliceQuad;
		Utility::atLineShader lineShader;
	};
}

