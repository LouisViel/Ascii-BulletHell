#include "../include/Vector3.h"

Vector3 Vector3::Zero = Vector3(0, 0, 0);

Vector3::Vector3() : x(0), y(0), z(0) { }

Vector3::Vector3(double _x, double _y) : x(_x), y(_y), z(0) { }

Vector3::Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }

Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) { }

Vector3& Vector3::operator =(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

bool Vector3::operator ==(const Vector3& other) const
{
	return other.x == x && other.y == y && other.z == z;
}

bool Vector3::operator !=(const Vector3& other) const
{
	return !(*this == other);
}

Vector3 Vector3::operator +(const Vector3& other) const
{
	return Vector3(
		x + other.x,
		y + other.y,
		z + other.z
	);
}

Vector3 Vector3::operator -(const Vector3& other) const
{
	return Vector3(
		x - other.x,
		y - other.y,
		z - other.z
	);
}

Vector3& Vector3::operator +=(const Vector3& other) 
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator -=(const Vector3& other) 
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}