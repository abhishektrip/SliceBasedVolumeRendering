#include <iostream>
#include "atRenderer.h"
using namespace atRenderEngine;

enum VolumeRenderingScenes
{
	BONSAI_OPACITY,
	BONSAI_TF,
	FOOT_OPACITY,
	FOOT_TF,
	ANEURYSM_OPACITY,
	ANEURYSM_TF,
};

void PrintUsage()
{
	int n;
	std::cout << "Usage : SliceBasedVolumeRendering [scene_enum]" << std::endl;
	std::cout << "scene_enum can be one of the following : 	BONSAI_OPACITY \n BONSAI_TF\n FOOT_OPACITY\n FOOT_TF\n HEAD_OPACITY\n HEAD_TF\n" << std::endl;
	std::cout << "Press any key to exit!" << std::endl;
	std::cin >> n;
}
void SetupDifferentScenes(atVolumeRenderingScene* scene, VolumeRenderingScenes enumScene)
{
	std::vector<Utility::TransferFunction1DPoint> colorPoints({
		Utility::TransferFunction1DPoint(Vector3f(.91f, .7f, .61f), 0),
		Utility::TransferFunction1DPoint(Vector3f(.91f, .7f, .61f), 80),
		Utility::TransferFunction1DPoint(Vector3f(1.0f, 1.0f, .85f), 82),
		Utility::TransferFunction1DPoint(Vector3f(1.0f, 1.0f, .85f), 256)
	});

	std::vector<Utility::TransferFunction1DPoint> anuerysmColorPoints({
		Utility::TransferFunction1DPoint(Vector3f(.54f, .27f, .07f), 0),
		Utility::TransferFunction1DPoint(Vector3f(.54f, .27f, .07f), 150),
		Utility::TransferFunction1DPoint(Vector3f(.0f, .0f, .85f), 156),
		Utility::TransferFunction1DPoint(Vector3f(.0f, .0f, .85f), 256)
	});

	std::vector<Utility::TransferFunction1DPoint> bonsaiColorPoints({
		Utility::TransferFunction1DPoint(Vector3f(0.22f, .37f, .04f), 0),
		Utility::TransferFunction1DPoint(Vector3f(0.22f, .37f, .04f), 50),
		Utility::TransferFunction1DPoint(Vector3f(.54f, .27f, .07f), 60),
		Utility::TransferFunction1DPoint(Vector3f(.54f, .27f, .07f), 150),
		Utility::TransferFunction1DPoint(Vector3f(1.0f, 1.0f, .85f), 156),
		Utility::TransferFunction1DPoint(Vector3f(1.0f, 1.0f, .85f), 256)
	});

	std::vector<Utility::TransferFunction1DPoint> bonsaiAlphaPoints({		
		Utility::TransferFunction1DPoint(0.0f, 0),
		Utility::TransferFunction1DPoint(0.0f, 30),
		Utility::TransferFunction1DPoint(0.3f, 50),
		Utility::TransferFunction1DPoint(1.0f, 256)
	});

	std::vector<Utility::TransferFunction1DPoint> grayPoints({
		Utility::TransferFunction1DPoint(Vector3f(.1f, .1f, .1f), 0),		
		Utility::TransferFunction1DPoint(Vector3f(1.0f, 1.0f, 1.0f), 256)
	});

	std::vector<Utility::TransferFunction1DPoint> alphaPoints({
		Utility::TransferFunction1DPoint(0.0f, 0),
		Utility::TransferFunction1DPoint(0.0f, 40),
		Utility::TransferFunction1DPoint(0.2f, 60),
		Utility::TransferFunction1DPoint(0.05f, 63),
		Utility::TransferFunction1DPoint(0.0f, 80),
		Utility::TransferFunction1DPoint(0.9f, 82),
		Utility::TransferFunction1DPoint(1.0f, 256)
	});

	switch (enumScene)
	{
	case BONSAI_OPACITY:
		scene->LoadRawVolume("../data/Volumes/Raw/bonsai.raw", 256, grayPoints, bonsaiAlphaPoints, 256, 256, 256);
		break;
	case BONSAI_TF:
		scene->LoadRawVolume("../data/Volumes/Raw/bonsai.raw", 256, bonsaiColorPoints, bonsaiAlphaPoints, 256, 256, 256);
		break;
	case FOOT_OPACITY:
		scene->LoadRawVolume("../data/Volumes/Raw/foot.raw", 256, grayPoints, alphaPoints, 256, 256, 256);
		break;
	case FOOT_TF:
		scene->LoadRawVolume("../data/Volumes/Raw/foot.raw", 256, colorPoints, alphaPoints, 256, 256, 256);
		break;
	case ANEURYSM_OPACITY:
		scene->LoadRawVolume("../data/Volumes/Raw/aneurism.raw", 256, grayPoints, alphaPoints, 256, 256, 256);
		break;
	case ANEURYSM_TF:
		scene->LoadRawVolume("../data/Volumes/Raw/aneurism.raw", 256, anuerysmColorPoints, alphaPoints, 256, 256, 256);
		break;
	default:
		break;
	}
}

int main(int argc, const char** argv)
{
	if (argc < 2)
	{
		PrintUsage();
		return 0;
	}

	atRenderer renderer;
	atCamera* camera = new atCamera();
	camera->SetPerspective(Utility::ToRadians(45.0f), 1080.0f / 1080.0f, 0.1f, 1000.0f);
	camera->SetLookAt(Vector3f(0, 0, 4), Vector3f(0, 0, 0), Vector3f(0, 1, 0));

	renderer.AddCamera(camera);
	renderer.Setup("Volume Rendering ", 1080, 1080);

	atVolumeRenderingScene* scene1 = new atVolumeRenderingScene();
	std::string sceneArg = argv[1];
	if(sceneArg.compare("BONSAI_OPACITY") == 0)
		SetupDifferentScenes(scene1, VolumeRenderingScenes::BONSAI_OPACITY);
	if (sceneArg.compare("BONSAI_TF") == 0)
		SetupDifferentScenes(scene1, VolumeRenderingScenes::BONSAI_TF);
	if (sceneArg.compare("FOOT_OPACITY") == 0)
		SetupDifferentScenes(scene1, VolumeRenderingScenes::FOOT_OPACITY);
	if (sceneArg.compare("FOOT_TF") == 0)
		SetupDifferentScenes(scene1, VolumeRenderingScenes::FOOT_TF);
	if (sceneArg.compare("ANEURYSM_OPACITY") == 0)
		SetupDifferentScenes(scene1, VolumeRenderingScenes::ANEURYSM_OPACITY);
	if (sceneArg.compare("ANEURYSM_TF") == 0)
		SetupDifferentScenes(scene1, VolumeRenderingScenes::ANEURYSM_TF);

	renderer.AddScene(scene1);
	renderer.Draw();
	return 1;
}



