#pragma once

#include <iostream>
#include <math.h>
#include "vec3.h"

namespace aven
{
	namespace math
	{
		struct Vec2
		{
			float x, y;

			Vec2();
			Vec2(const float& x, const float& y);
			Vec2(const Vec3& vector);

			Vec2& add(const Vec2& other);
			Vec2& subtract(const Vec2& other);
			Vec2& multiply(const Vec2& other);
			Vec2& divide(const Vec2& other);

			friend Vec2 operator+(Vec2 left, const Vec2& right);
			friend Vec2 operator-(Vec2 left, const Vec2& right);
			friend Vec2 operator*(Vec2 left, const Vec2& right);
			friend Vec2 operator/(Vec2 left, const Vec2& right);

			friend Vec2 operator+(Vec2 left, float value);
			friend Vec2 operator*(Vec2 left, float value);

			bool operator==(const Vec2& other);
			bool operator!=(const Vec2& other);

			Vec2& operator+=(const Vec2& other);
			Vec2& operator-=(const Vec2& other);
			Vec2& operator*=(const Vec2& other);
			Vec2& operator/=(const Vec2& other);

			float magnitude() const;
			Vec2 normalize() const;
			float distance(const Vec2& other) const;
			float dot(const Vec2& other) const;

			friend std::ostream& operator<<(std::ostream& stream, const Vec2& vector);
		};
	}
}