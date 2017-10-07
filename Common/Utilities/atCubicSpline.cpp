#include "atCubicSpline.h"
using namespace atRenderEngine::Utility;

atCubicSpline::atCubicSpline(Vector4f a, Vector4f b, Vector4f c, Vector4f d)
	:mA(a),mB(b),mC(c),mD(d)
{
}

Vector4f atRenderEngine::Utility::atCubicSpline::GetPointOnSpline(float s)
{
	return (((((mD * s) + mC) * s + mB) * s) + mA);
}

std::vector<atCubicSpline> atRenderEngine::Utility::CalculateCubicSpline(int n, std::vector<TransferFunction1DPoint> v)
{
	std::vector<Vector4f> gamma(n + 1);
	std::vector<Vector4f> delta(n + 1);
	std::vector<Vector4f> D(n + 1);
	int i;
	/* We need to solve the equation
	* taken from: http://mathworld.wolfram.com/CubicSpline.html
	[2 1       ] [D[0]]   [3(v[1] - v[0])  ]
	|1 4 1     | |D[1]|   |3(v[2] - v[0])  |
	|  1 4 1   | | .  | = |      .         |
	|    ..... | | .  |   |      .         |
	|     1 4 1| | .  |   |3(v[n] - v[n-2])|
	[       1 2] [D[n]]   [3(v[n] - v[n-1])]

	by converting the matrix to upper triangular.
	The D[i] are the derivatives at the control points.
	*/

	Vector4f denominator;
	//this builds the coefficients of the left matrix
	gamma[0] = Vector4f::Zero();
	gamma[0].x() = 1.0f / 2.0f;
	gamma[0].y() = 1.0f / 2.0f;
	gamma[0].z() = 1.0f / 2.0f;
	gamma[0].w() = 1.0f / 2.0f;
	for (i = 1; i < n; i++)
	{
		denominator = ((4 * Vector4f::Ones()) - gamma[i - 1]);
		gamma[i] = Vector4f::Ones();
		gamma[i].x() = 1.0f / denominator.x();
		gamma[i].y() = 1.0f / denominator.y();
		gamma[i].z() = 1.0f / denominator.z();
		gamma[i].w() = 1.0f / denominator.w();
	}
	denominator = ((2 * Vector4f::Ones()) - gamma[n - 1]);
	gamma[n] = Vector4f::Ones();
	gamma[n].x() = 1.0f / denominator.x();
	gamma[n].y() = 1.0f / denominator.y();
	gamma[n].z() = 1.0f / denominator.z();
	gamma[n].w() = 1.0f / denominator.w();

	delta[0] = (3 * (v[1].colorValue - v[0].colorValue)).cwiseProduct(gamma[0]);
	for (i = 1; i < n; i++)
	{
		delta[i] = (3 * (v[i + 1].colorValue - v[i - 1].colorValue) - delta[i - 1]).cwiseProduct(gamma[i]);
	}
	delta[n] = (3 * (v[n].colorValue - v[n - 1].colorValue) - delta[n - 1]).cwiseProduct(gamma[n]);

	D[n] = delta[n];
	for (i = n - 1; i >= 0; i--)
	{
		D[i] = delta[i] - (gamma[i].cwiseProduct(D[i + 1]));
	}

	// now compute the coefficients of the cubics 
	std::vector<atCubicSpline> C(n);
	for (i = 0; i < n; i++)
	{
		C[i] = atCubicSpline(v[i].colorValue, D[i], 3 * (v[i + 1].colorValue - v[i].colorValue) - 2 * D[i] - D[i + 1],
			2 * (v[i].colorValue - v[i + 1].colorValue) + D[i] + D[i + 1]);
	}
	return C;
}
