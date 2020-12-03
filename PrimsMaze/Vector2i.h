#pragma once
#include <iostream>

class Vector2
{
public:
	Vector2(int x = 0, int y = 0);
	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator*(int rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	bool operator==(Vector2& rhs) const;
	bool operator==(const Vector2& rhs) const;
	bool operator!=(Vector2& rhs) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector2& dt);

	int x;
	int y;
};