#pragma once

template <class T>
class Vector2D
{
private: 
	T _x;
	T _y;
public:

	//constructoras
	Vector2D() _x(0), _y(0) {};
	Vector2D(T x, T y) _x(x), _y(y) {};

	//Getter de x
	T getX() { return x } const;
	//Getter de y
	T getY() { return y } const;

	//aritmética

	Vector2D operator +(const Vector2D& u, const Vector2D& v) const { return Vector2D(u.x + v.x , u.y + v.y) };
	Vector2D operator -(const Vector2D& u, const Vector2D& v) const { return Vector2D(u.x - v.x , u.y - v.y) };
	Vector2D operator *(const Vector2D& u, const Vector2D& v) const { return Vector2D(u.x * v.x , u.y * v.y) };
	Vector2D operator *(T k , const Vector2D& u) const { return Vector2D(k*u.x , k*u.y)};
};

template<class T>
using Point2D = Vector2D;