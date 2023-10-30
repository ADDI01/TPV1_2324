#pragma once

template <class T>
class Vector2D
{
private:
	T _x;
	T _y;

public:
	//Constructoras
	Vector2D() : _x(0), _y(0) {};
	Vector2D(T x, T y) : _x(x), _y(y) {};
	Vector2D(Vector2D& v) : _x(v._x), _y(v._y) {};

	//Getter de _x e _y
	T getX() const { return _x; };
	T getY() const { return _y; };

	//Sobrecarga operadores
	Vector2D operator+(const Vector2D& v) const {
		Vector2D r;
		r._x = this->_x + v._x;
		r._y = this->_y + v._y;
		return r;
	}

	Vector2D operator-(const Vector2D& v) const {
		Vector2D r;
		r._x = this->_x - v._x;
		r._y = this->_y - v._y;
		return r;
	}
	Vector2D operator*(T d) const {
		Vector2D r;
		r._x = _x * d;
		r._y = _y * d;
		return r;
	}
	double operator*(const Vector2D& d) const {
		return d._x * _x + d._y * _y;
	}

};

template <class T>
using Point2D = Vector2D<T>;



