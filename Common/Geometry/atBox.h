#pragma once
#include "atStandardShape.h"

namespace atRenderEngine
{
	class atBox : public atStandardShape
	{
	public:
		atBox();
		~atBox();
		void FindMinMax(Utility::MinMaxPair& result);
		std::vector<Vector2i> mEdgeList;
		void SetYRotation(float degree) override;
		Vector3f mColor;
		std::vector<Vector3f> DrawableBoxVertices();
		std::vector<Vector3f> DrawableBoxColors();

	};
}

