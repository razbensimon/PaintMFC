#include "pch.h"
#include "Triangle.h"
#include "FIGURES.h"

using namespace shapes;

void Triangle::recalculatePointsFromCircumscribedRectangle()
{
	const int halfWidth = (getX2() - getX1()) / 2;

	delete[] _points;
	_points = new POINT[]{
		{getX1() , getY1()},
		{getX2() , getY1()},
		{getX1() + halfWidth, getY2()}
	};
}

json Triangle::toJson() const
{
	json figure = Figure::toJson();
	figure["type"] = FIGURES::TRIANGLE;
	return  figure;
}