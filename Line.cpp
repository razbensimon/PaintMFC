#include "pch.h"
#include "Line.h"

#include "FIGURES.h"

using namespace shapes;

void Line::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	displayContext->SelectObject(&pen);

	displayContext->MoveTo(getX1(), getY1());
	displayContext->LineTo(getX2(), getY2());
}

json Line::toJson() const
{
	json figure = Figure::toJson();
	figure["type"] = FIGURES::LINE;
	return  figure;
}

bool Line::isContains(const POINT& point) {
	const double m = (getY2() - getY1()) / double(getX2() - getX1());
	const double n = getY1() - m * getX1();
	const double distance = abs((m * point.x - point.y + n) / sqrt(m * m + 1));
		
	if (distance <= getPenWidth())
		return Figure::isContains(point);
	return false;
}
