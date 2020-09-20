#include "pch.h"
#include "Line.h"

using namespace shapes;

void Line::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	displayContext->SelectObject(&pen);

	displayContext->MoveTo(getX1(), getY1());
	displayContext->LineTo(getX2(), getY2());
}