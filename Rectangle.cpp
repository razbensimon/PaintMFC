#include "pch.h"
#include "Rectangle.h"

using namespace shapes;

void Rectangle::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	displayContext->SelectObject(&pen);
	CBrush brush(getFillColor());
	displayContext->SelectObject(&brush);

	displayContext->Rectangle(getX1(), getY1(), getX2(), getY2());
}
