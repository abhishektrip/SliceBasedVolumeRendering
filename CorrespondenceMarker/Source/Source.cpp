#include <iostream>
#include "atRenderer.h"
using namespace atRenderEngine;

int main()
{
#ifdef __NOT_EGG
	atRenderer renderer;

	atCamera* camera = new atCamera();
	camera->SetPerspective(Utility::ToRadians(135.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
	camera->SetLookAt(Vector3f(0, 5, 30), Vector3f(0, 5, 0), Vector3f(0, 1, 0));

	renderer.AddCamera(camera);
	renderer.Setup("Marker Generation ", 1920, 1080);
	//camera->SetModel(Eigen::Matrix4f::Identity());
	atScene* scene1 = new atScene();
	//scene1->LoadMesh("../data/ScannedHead.obj", false, true, Vector3f(-2, 0, 0));
	scene1->LoadMesh("../data/M3DFigures/M3DFigures/Male/M3DMale_LOD0_shape.obj", false, true, Vector3f(-10, 0, 0), Vector3f(0.1, 0.1, 0.1));
	//scene1->LoadMesh("../data/camel_ref.obj", false, true , Vector3f(0,0,-1));

	atScene* scene2 = new atScene();
	//scene2->LoadMesh("../data/M3dMale_Head.obj", false, true, Vector3f(2, 0, 0));
	scene2->LoadMesh("../data/M3DFigures/M3DFigures/Male/M3DMale_Nekei_shape.obj", false, true, Vector3f(10, 0, 0), Vector3f(0.1, 0.1, 0.1));
	//scene2->LoadMesh("../data/camel_ref.obj", false, true, Vector3f(0, 0, 1.0));
	/*scene1->LoadMesh("../data/POINT.DAT", false, true);

	atScene* scene3 = new atScene();
	scene3->LoadMesh("../data/BARREL.DAT", true, true);
	*/
	renderer.AddScene(scene1);
	renderer.AddScene(scene2);
	/*renderer.AddScene(scene3);*/

	renderer.Draw();
#else // __NOT_EGG

	// EGG SETUP
	atRenderer renderer;
	atCamera* camera = new atCamera();
	camera->SetPerspective(Utility::ToRadians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
	camera->SetLookAt(Vector3f(0, 5, 30), Vector3f(0, 5, 0), Vector3f(0, 1, 0));

	renderer.AddCamera(camera);
	renderer.Setup("Marker Generation ", 1920, 1080);

	atScene* scene1 = new atScene();
	scene1->LoadMesh("../data/EggData/BARREL.DAT", true,true);

	atScene* scene2 = new atScene();
	scene2->LoadMesh("../data/EggData/POINT.DAT", false , true);

	atScene* scene3 = new atScene();
	scene3->LoadMesh("../data/EggData/END.DAT", false, true);

	renderer.AddScene(scene1);
	renderer.Draw();
#endif
	return 1;
}