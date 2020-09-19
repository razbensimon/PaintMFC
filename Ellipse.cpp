#include "pch.h"
#include "Ellipse.h"


using namespace shapes;

void Ellipse::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	displayContext->SelectObject(&pen);
	CBrush brush(getFillColor());
	displayContext->SelectObject(&brush);
	
	displayContext->Ellipse(getX1(), getY1(), getX2(), getY2());
}
