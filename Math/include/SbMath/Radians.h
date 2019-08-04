#pragma once
#include "Constants.h"

namespace sb_math
{
	constexpr float RADIANS_TO_DEGREES{ 360.0f / (2.0f * PI) };

	constexpr float DEGREES_TO_RADIANS{ 2.0f * PI / 360.0f };


	inline float toRadians(float degrees)
	{
		return degrees * DEGREES_TO_RADIANS;
	}

	inline float toDegrees(float radians)
	{
		return radians * RADIANS_TO_DEGREES;
	}
}