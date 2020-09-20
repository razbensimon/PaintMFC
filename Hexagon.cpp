#include "pch.h"
#include "Hexagon.h"
#include "FIGURES.h"

using namespace shapes;

void Hexagon::recalculatePointsFromCircumscribedRectangle()
{
	const int thirdWidth = (getX2() - getX1()) / 3;
	const int halfHeight = (getY2() - getY1()) / 2;

	delete[] _points;
	_points = new POINT[]{
		{getX1(), getY1() + halfHeight},
		{getX1() + thirdWidth, getY1()},
		{getX1() + thirdWidth + thirdWidth, getY1()},
		{getX2(), getY1() + halfHeight},
		{getX2() - thirdWidth, getY2()},
		{getX2() - thirdWidth - thirdWidth, getY2()},
	};
}

json Hexagon::toJson() const
{
	json figure = Figure::toJson();
	figure["type"] = FIGURES::HEXAGON;
	return  figure;
}