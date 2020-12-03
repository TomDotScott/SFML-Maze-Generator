#include "Vector2i.h"
#include <cmath>
#include "constants.h"

Vector2::Vector2(const int _x, const int _y) :
	x(_x),
	y(_y)
{
}

// Operators
Vector2 Vector2::operator +(const Vector2& rhs) const
{
	return{ this->x + rhs.x, this->y + rhs.y };
}

Vector2 Vector2::operator*(const int rhs) const
{
	return{ this->x * rhs, this->y * rhs };
}

Vector2 Vector2::operator -(const Vector2& rhs) const
{
	return{ rhs.x - this->x, rhs.y - this->y };
}

bool Vector2::operator==(Vector2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(Vector2& rhs) const
{
	return x != rhs.x || y != rhs.y;
}

std::ostream& operator<<(std::ostream& os, const Vector2& dt)
{
	return os << "X: " << dt.x << " Y: " << dt.y;
}