#pragma once
#include <AntTweakBar.h>
#include <atUtility.h>

namespace atRenderEngine
{
	class atUserInterface
	{
	public:
		atUserInterface(int width, int height);
		~atUserInterface();
		virtual void Draw();

		int width = 640, height = 480;
		int bpp, flags;
		int quit = 0;
		TwBar *bar;
		int n, numCubes = 30;
		Eigen::Vector3f color0{ 1.0f, 0.5f, 0.0f };
		Eigen::Vector3f color1{ 0.5f, 1.0f, 0.0f };
		double ka = 5.3, kb = 1.7, kc = 4.1;

	};
}
