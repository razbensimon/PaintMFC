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
	const auto rectangle = this->getRect();
	
	if (point.x >= rectangle.left && point.x <= rectangle.right && point.y <= rectangle.bottom && point.y >= rectangle.top)
		return true;	

	return false;
}

RECT Figure::getRect() const
{
	const auto leftX = min(getX1(), getX2());
	const auto rightX = max(getX1(), getX2());
	const auto topY = min(getY1(), getY2()); // top and bottom are reversed because top-left is (0,0)
	const auto bottomY = max(getY1(), getY2());

	RECT rect;
	rect.left = leftX;
	rect.right = rightX;
	rect.top = topY;
	rect.bottom = bottomY;	
	return rect;
}
