#include "pch.h"
#include "Ellipse.h"


using namespace shapes;

void Ellipse::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	CPen* old_pen = displayContext->SelectObject(&pen);
	displayContext->Ellipse(getX1(), getY1(), getX2(), getY2());
	displayContext->SelectObject(old_pen);
}
