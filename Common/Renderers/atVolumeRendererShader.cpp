#include "atVolumeRendererShader.h"

using namespace atRenderEngine::Utility;

atVolumeRenderingShader::atVolumeRenderingShader()
{
	mProgramId = Utility::atLoadShaders("../Common/Shaders/VolumeRenderer.vs", "../Common/Shaders/VolumeRenderer.fs");
}
atVolumeRenderingShader::~atVolumeRenderingShader()
{
}

void atRenderEngine::Utility::atVolumeRenderingShader::Setup(atQuad& quad, const char * volume, std::vector<Vector4f>& transferFunction, unsigned int xRange, unsigned int yRange, unsigned int zRange)
{
	SetupQuadRendering(quad);
	Setup3DTexture(volume, xRange, yRange, zRange);
	Setup1DTexture(transferFunction);
}

void atRenderEngine::Utility::atVolumeRenderingShader::Setup(atBox& quad, const char * volume, unsigned int xRange, unsigned int yRange, unsigned int zRange)
{
	SetupBoxRendering(quad,0);
	Setup3DTexture(volume, xRange, yRange, zRange);
}

void atVolumeRenderingShader::Draw(std::vector<Vector3f>& vertexArray, std::vector<Vector3f>& colorArray, Matrix4f& MVPMatrix)
{

}

void atRenderEngine::Utility::atVolumeRenderingShader::Draw(atQuad& quad, int numberOfSlices, Matrix4f & viewMatrix, Matrix4f & projectionMatrix, Matrix4f& textureMatrix)
{
	Matrix4f currentModeMat = quad.GetModel();
	Matrix4f MVPMatrix = projectionMatrix * viewMatrix * currentModeMat;
	glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, MVPMatrix.data());
	glUniformMatrix4fv(mModelMatrixID, 1, GL_FALSE, currentModeMat.data());
	glUniformMatrix4fv(mViewMatrixID, 1, GL_FALSE, viewMatrix.data());
	glUniformMatrix4fv(mTextureMatrixID, 1, GL_FALSE, textureMatrix.data());

	for (int i = 0; i < numberOfSlices; i++)
	{
		//std::cout << "Z coordinate : " << ((float)(0.5f + i) / ((float)numberOfSlices)) - 0.5f << std::endl;
		int sNumber = glGetUniformLocation(mProgramId, "sliceNumber");
		glUniform1f(sNumber, ((float)(i) / ((float)numberOfSlices)) - 0.5f);

		int totalSliceNum = glGetUniformLocation(mProgramId, "totalSlices");
		glUniform1f(totalSliceNum, ((float)(0.5f + i)/((float)numberOfSlices)));

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		//2nd attribute buffer : UVs
		if (quad.mUVList.size() > 0)
		{
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, mUVVertexBuffer);
			glVertexAttribPointer(
				1,                                // attribute
				2,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);
		}
		if (quad.NumberofNormals() > 0)
		{
			// 3rd attribute buffer : normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
			glVertexAttribPointer(
				2,                                // attribute
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);

		}

		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_3D, mVolumeTexture);
		glUniform1i(mVolumeTextureId, 0);

		//Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}

void atRenderEngine::Utility::atVolumeRenderingShader::Draw(atBox& quad, int numberOfSlices, Matrix4f & viewMatrix, Matrix4f & projectionMatrix)
{
	Matrix4f currentModeMat = quad.GetModel();
	Matrix4f MVPMatrix = projectionMatrix * viewMatrix * currentModeMat;
	glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, MVPMatrix.data());
	glUniformMatrix4fv(mModelMatrixID, 1, GL_FALSE, currentModeMat.data());
	glUniformMatrix4fv(mViewMatrixID, 1, GL_FALSE, viewMatrix.data());

	/*for (int i = 0; i < numberOfSlices; i++)
	{*/

		//int sNumber = glGetUniformLocation(mProgramId, "sliceNumber");
		//glUniform1i(sNumber, i);

		//int totalSliceNum = glGetUniformLocation(mProgramId, "totalSlices");
		//glUniform1f(totalSliceNum, ((float)(0.5f + i) / ((float)numberOfSlices)));

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		//2nd attribute buffer : UVs
		if (quad.mUVList.size() > 0)
		{
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, mUVVertexBuffer);
			glVertexAttribPointer(
				1,                                // attribute
				2,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);
		}
		if (quad.NumberofNormals() > 0)
		{
			// 3rd attribute buffer : normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
			glVertexAttribPointer(
				2,                                // attribute
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);

		}

		// Set our "VolumeTexure" sampler to user Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_3D, mVolumeTexture);
		glUniform1i(mVolumeTextureId, 0);

		// Set our "TransferFunction" sampler to user Texture Unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_1D, mTransferFunctionTexture);
		glUniform1i(mTransferFunctionTextureId, 1);

		//Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	//}
}

void atRenderEngine::Utility::atVolumeRenderingShader::Setup3DTexture(const char * volume, unsigned int xRange, unsigned int yRange, unsigned int zRange)
{

	glGenTextures(1, &mVolumeTexture);

	// bind 3D texture target
	glBindTexture(GL_TEXTURE_3D, mVolumeTexture);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	// pixel transfer happens here from client to OpenGL server
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, xRange, yRange, zRange, 0, GL_RED, GL_UNSIGNED_BYTE, volume);
	//glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, xRange, yRange, zRange, 0, GL_RGBA, GL_UNSIGNED_BYTE, volume);

	mVolumeTextureId = glGetUniformLocation(mProgramId, "VolumeTex");

	//glUniform1i(mVolumeTextureId, 0);

}

void atRenderEngine::Utility::atVolumeRenderingShader::Setup1DTexture(std::vector<Vector4f>& transferFunction)
{		
	glGenTextures(1, &mTransferFunctionTexture);
	glBindTexture(GL_TEXTURE_1D, mTransferFunctionTexture);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_RGBA, GL_FLOAT, transferFunction.data());	

	mTransferFunctionTextureId = glGetUniformLocation(mProgramId, "TransferFunction");
}

void atRenderEngine::Utility::atVolumeRenderingShader::SetupQuadRendering(atQuad& quad)
{
	//Setup Vertex Array
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	if (quad.NumberofNormals() > 0)
	{
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*quad.NumberOfVertices(), &(quad.VertexList()[0]), GL_STATIC_DRAW);
	}

	if (quad.mUVList.size() > 0)
	{
		glGenBuffers(1, &mUVVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mUVVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, quad.mUVList.size() * sizeof(Vector2f), &(quad.mUVList[0]), GL_STATIC_DRAW);
	}

	if (quad.NumberofNormals() > 0)
	{
		glGenBuffers(1, &mNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, quad.NumberofNormals() * sizeof(Vector3f), quad.NormalList().data(), GL_STATIC_DRAW);
	}

	// Generate a buffer for the indices as well
	indices.clear();
	quad.ConvertTriangleToVertIndexList(indices);

	if (indices.size() > 0)
	{
		glGenBuffers(1, &mElementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	// Get a handle for our "MVP" uniform
	mMatrixID = glGetUniformLocation(mProgramId, "MVP");
	mViewMatrixID = glGetUniformLocation(mProgramId, "V");
	mModelMatrixID = glGetUniformLocation(mProgramId, "M");
	mTextureMatrixID = glGetUniformLocation(mProgramId, "T");
}

void atRenderEngine::Utility::atVolumeRenderingShader::SetupBoxRendering(atBox & box, int slices)
{
	//Setup Vertex Array
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	if (box.NumberofNormals() > 0)
	{
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*box.NumberOfVertices(), &(box.VertexList()[0]), GL_STATIC_DRAW);
	}

	if (box.mUVList.size() > 0)
	{
		glGenBuffers(1, &mUVVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mUVVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, box.mUVList.size() * sizeof(Vector2f), &(box.mUVList[0]), GL_STATIC_DRAW);
	}

	if (box.NumberofNormals() > 0)
	{
		glGenBuffers(1, &mNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, box.NumberofNormals() * sizeof(Vector3f), box.NormalList().data(), GL_STATIC_DRAW);
	}

	// Generate a buffer for the indices as well
	indices.clear();
	box.ConvertTriangleToVertIndexList(indices);

	if (indices.size() > 0)
	{
		glGenBuffers(1, &mElementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	// Get a handle for our "MVP" uniform
	mMatrixID = glGetUniformLocation(mProgramId, "MVP");
	mViewMatrixID = glGetUniformLocation(mProgramId, "V");
	mModelMatrixID = glGetUniformLocation(mProgramId, "M");
	mTextureMatrixID = glGetUniformLocation(mProgramId, "T");
}

