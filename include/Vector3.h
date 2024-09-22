#pragma once

struct Vector3
{
public:
	static Vector3 Zero;

	double x;
	double y;
	double z;

	Vector3();
	Vector3(double x, double y);
	Vector3(double x, double y, double z);

	Vector3& operator = (const Vector3&);
	Vector3(const Vector3&);

	bool operator ==(const Vector3& other) const;
	bool operator !=(const Vector3& other) const;
	Vector3 operator +(const Vector3& other) const;
	Vector3 operator -(const Vector3& other) const;
	Vector3& operator +=(const Vector3& other);
	Vector3& operator -=(const Vector3& other);
};