#pragma once
#include "atShader.h"
#include "atBox.h"
#include "atQuad.h"

namespace atRenderEngine
{
	namespace Utility
	{
		class atVolumeRenderingShader :
			public atShader
		{
		public:
			atVolumeRenderingShader();
			~atVolumeRenderingShader();
			GLuint VolumeTexture() { return mVolumeTexture; }
			void Setup(atQuad& quad, const char* volume, std::vector<Vector4f>& transferFunction, unsigned int xRange, unsigned int yRange, unsigned int zRange);
			void Setup(atBox& quad, const char* volume, unsigned int xRange, unsigned int yRange, unsigned int zRange);
			void Draw(std::vector<Vector3f>& vertexArray, std::vector<Vector3f>& colorArray, Matrix4f& MVPMatrix);
			void Draw(atQuad& quad, int numberOfSlices, Matrix4f& viewMatrix, Matrix4f& projectionMatrix, Matrix4f& textureMatrix);
			void Draw(atBox& quad, int numberOfSlices, Matrix4f& viewMatrix, Matrix4f& projectionMatrix);
		private:
			void Setup3DTexture(const char* volume, unsigned int xRange, unsigned int yRange, unsigned int zRange);
			void Setup1DTexture(std::vector<Vector4f>& transferFunction);
			void SetupQuadRendering(atQuad& quad);
			void SetupBoxRendering(atBox& box, int slices);

			//member variables
			GLuint mTransferFunctionTexture;
			GLuint mTransferFunctionTextureId;
			GLuint mVolumeTexture;
			GLuint mVolumeTextureId;
			GLuint mElementbuffer;
			GLuint mVertexArrayID;
			GLuint mVertexBuffer;
			GLuint mUVVertexBuffer;
			GLuint mNormalBuffer;
			GLuint mMatrixID;
			GLuint mViewMatrixID;
			GLuint mModelMatrixID;
			GLuint mTextureMatrixID;

			std::vector<unsigned int> indices;
			std::vector<GLfloat> mVertexBufferData;
			//atBox mBox;
		};
	}
}