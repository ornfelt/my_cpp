#pragma once

#include <complex>

using complex = std::complex<double>;

struct Point
{
	Point() :
		x(0.0),
		y(0.0)
	{}

	operator complex() const
	{
		return complex(x, y);
	}

	Point(double x_, double y_) :
		x(x_),
		y(y_)
	{}

	void operator+=(const Point& p)
	{
		x += p.x;
		y += p.y;
	}

	double x, y;
};

struct PolarPoint
{
	PolarPoint() :
		r(0.0),
		a(0.0)
	{}

	PolarPoint(double r_, double a_) :
		r(r_),
		a(a_)
	{}

	PolarPoint(const Point& point)
	{
		double vx(point.x);
		double vy(point.y);

		r = sqrt(vx*vx + vy * vy);
		a = acos(vx / r);
		if (vy < 0)
			a *= -1.0;
	}

	double r, a;
};


double distance(const Point& p1, const Point& p2 = Point(0.0, 0.0))
{
	double vx(p1.x - p2.x);
	double vy(p1.y - p2.y);

	return sqrt(vx*vx + vy*vy);
}

Point operator-(const Point& p1, const Point& p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator+(const Point& p1, const Point& p2)
{
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator*(float f, const Point& p1)
{
	return Point(p1.x*f, p1.y*f);
}
