#include "pch.h"
#include "Rectangle.h"

void Rectangle::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	CPen* old_pen = displayContext->SelectObject(&pen);
	displayContext->Rectangle(getX1(), getY1(), getX2(), getY2());
	displayContext->SelectObject(old_pen);
}
