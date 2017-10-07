#pragma once
#include "atUtility.h"


namespace atRenderEngine
{
	namespace Utility
	{
		class atCubicSpline
		{
		public:
			atCubicSpline() {}
			atCubicSpline(Vector4f a, Vector4f b, Vector4f c, Vector4f d);
			//evaluate the point using a cubic equation
			Vector4f GetPointOnSpline(float s);			
		private:
			Vector4f mA, mB, mC, mD;
		};

		std::vector<atCubicSpline> CalculateCubicSpline(int n, std::vector<TransferFunction1DPoint> v);

	}
}