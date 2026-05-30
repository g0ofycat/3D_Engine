#pragma once

#include <iostream>

// ====== math_lib ======

class math_lib
{
	public:
		/// @brief Lerps a value between two points
		/// @tparam T: Type of the values
		/// @param a: Start value
		/// @param b: End value
		/// @param t: Interpolation factor (0.0 to 1.0)
		/// @return T: The lerped value
		template <typename T>
			static T lerp(T a, T b, T t)
			{
				return a + (b - a) * t;
			}
};
