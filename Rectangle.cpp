#include "pch.h"
#include "Rectangle.h"
#include "FIGURES.h"

using namespace shapes;

void Rectangle::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	displayContext->SelectObject(&pen);
	CBrush brush(getFillColor());
	displayContext->SelectObject(&brush);

	displayContext->Rectangle(getX1(), getY1(), getX2(), getY2());
}

json Rectangle::toJson() const
{
	json figure = Figure::toJson();
	figure["type"] = FIGURES::RECTANGLE;
	return  figure;
}