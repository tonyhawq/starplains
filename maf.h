#pragma once

#include <cmath>

namespace maf
{
	constexpr double PI = 3.141592653589793238462643383279502884197169399375105820974944;
	constexpr float PI_f = (float)PI;
	constexpr double deg_to_rad = PI / double(180);
	constexpr float deg_to_rad_f = (float)deg_to_rad;
	constexpr double rad_to_deg = double(180) / PI;
	constexpr float rad_to_deg_f = (float)rad_to_deg;
	constexpr float one_turn = 360.0f * deg_to_rad;
	struct fvec2
	{
		float x = 0;
		float y = 0;
		float mag() const
		{
			return sqrtf((x * x) + (y * y));
		}
		float distSqr(const fvec2& b) const
		{
			return (this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y);
		}
		float dist(const fvec2& b) const
		{
			return sqrtf((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y));
		}
		float dot(const fvec2& b) const
		{
			/*float amag = this->mag();
			float bmag = b.mag();
			float theta = atan2f(b.y, b.x) - atan2f(this->y, this->x);
			return amag * bmag * cosf(theta);*/
			return this->x * b.x + this->y * b.y;
		}
		fvec2 rotate(float angle) const
		{
			return {
				this->x * cosf(angle) - this->y * sinf(angle),
				this->x * sinf(angle) + this->y * cosf(angle),
			};
		}
		fvec2 rotate_c(float cosine, float sine) const
		{
			return {
				this->x * cosine - this->y * sine,
				this->x * sine + this->y * cosine
			};
		}
		fvec2 normalize() const
		{
			float mag = this->mag();
			return { this->x / mag, this->y / mag };
		}
		bool operator==(const fvec2& other) const
		{
			return (this->x == other.x && this->y == other.y);
		}
		fvec2 operator+(const fvec2& other) const
		{
			return { this->x + other.x, this->y + other.y };
		}
		fvec2 operator-(const fvec2& other) const
		{
			return { this->x - other.x, this->y - other.y };
		}
		fvec2 operator*(const float& other) const
		{
			return { this->x * other, this->y * other };
		}
		void operator+=(const fvec2& other)
		{
			this->x += other.x;
			this->y += other.y;
		}
		void operator-=(const fvec2& other)
		{
			this->x -= other.x;
			this->y -= other.y;
		}
		void operator*=(const float& other)
		{
			this->x *= other;
			this->y *= other;
		}
	};
	struct fvec4
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};
	/// <summary>
	/// this is used by like one function but i cba to just make an array for it
	/// </summary>
	struct point4
	{
		fvec2 a;
		fvec2 b;
		fvec2 c;
		fvec2 d;
	};
}
