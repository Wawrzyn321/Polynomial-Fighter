#ifndef FLOAT_COLOR_H
#define FLOAT_COLOR_H

#include "Utility.h"

class FloatColor
{
	const float colorRange = 255.0f;
	const float colorRangeReciproc = 1 / colorRange;
public:
	float x, y, z, w;

	FloatColor(){}

	FloatColor(const sf::Color color)
	{
		x = static_cast<float>(color.r)*colorRangeReciproc;
		y = static_cast<float>(color.g)*colorRangeReciproc;
		z = static_cast<float>(color.b)*colorRangeReciproc;
		w = static_cast<float>(color.a)*colorRangeReciproc;
	}

	sf::Color toColor() const
	{
		float r = x*colorRange;
		float g = y*colorRange;
		float b = z*colorRange;
		float a = w*colorRange;
		return sf::Color((sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b, (sf::Uint8)a);
	}

	FloatColor lerpTo(const FloatColor to, float t, bool clampT = true)
	{
		if (clampT) {
			t = clamp(t, 0.0f, 1.0f);
		}
		x += (to.x - x)*t;
		y += (to.y - y)*t;
		z += (to.z - z)*t;
		w += (to.w - w)*t;
		return *this;
	}

	FloatColor & operator =(const FloatColor & rhs)
	{
		if (&rhs != this)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
		}
		return *this;
	}

	float calculateMaxDifference(const FloatColor& other, bool includeAlpha = false) const
	{
		float r = std::abs(x - other.x);
		float g = std::abs(y - other.y);
		float b = std::abs(z - other.z);
		if (includeAlpha) {
			float a = std::abs(w - other.w);
			return std::max(std::max(r, g), std::max(b, a));
		}
		else {
			return std::max(std::max(r, g), b);
		}

	}
};

#endif