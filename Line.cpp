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
	double m = double(this->getY2() - this->getY1()) / double(this->getX2() - this->getX1());
	double left = double(point.y - this->getY1());
	double right = m * double(point.x - this->getX1());
	if (abs(left - right) <= 3)
		return true;
	else
		return false;
}
