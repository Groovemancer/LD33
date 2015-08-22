#pragma once

#include <iostream>

namespace aven
{
	namespace math
	{
		struct Vec2;

		struct Vec3
		{
			float x, y, z;

			Vec3();
			Vec3(const float& x, const float& y, const float& z);
			Vec3(const Vec2& other);

			Vec3& add(const Vec3& other);
			Vec3& subtract(const Vec3& other);
			Vec3& multiply(const Vec3& other);
			Vec3& divide(const Vec3& other);

			friend Vec3 operator+(Vec3 left, const Vec3& right);
			friend Vec3 operator-(Vec3 left, const Vec3& right);
			friend Vec3 operator*(Vec3 left, const Vec3& right);
			friend Vec3 operator/(Vec3 left, const Vec3& right);

			bool operator==(const Vec3& other);
			bool operator!=(const Vec3& other);

			Vec3& operator+=(const Vec3& other);
			Vec3& operator-=(const Vec3& other);
			Vec3& operator*=(const Vec3& other);
			Vec3& operator/=(const Vec3& other);

			float distance(const Vec3& other) const;

			friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
		};
	}
}