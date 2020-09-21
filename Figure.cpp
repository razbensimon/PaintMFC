#include "pch.h"
#include "Figure.h"

using namespace shapes;

json Figure::toJson() const
{
	json figure;
	figure["x1"] = getX1();
	figure["y1"] = getY1();
	figure["x2"] = getX2();
	figure["y2"] = getY2();
	figure["penWidth"] = getPenWidth();
	figure["color"] = getColor();
	figure["fillColor"] = getFillColor();

	return figure;
}

bool Figure::isContains(const POINT& point)
{
	const auto leftX = min(getX1(), getX2());
	const auto rightX = max(getX1(), getX2());
	const auto topY = max(getY1(), getY2());
	const auto bottomY = min(getY1(), getY2());

	if (point.x >= leftX && point.x <= rightX && point.y <= topY && point.y >= bottomY)
	{
		return true;
	}

	return false;
}
