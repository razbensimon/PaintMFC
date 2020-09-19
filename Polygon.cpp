#include "pch.h"
#include "Polygon.h"

void Polygon::draw(CDC* displayContext) const
{
	CPen pen(PS_SOLID, getPenWidth(), getColor());
	displayContext->SelectObject(&pen);
	CBrush brush(getFillColor());
	displayContext->SelectObject(&brush);

	displayContext->Polygon(getPoints(), getPointsNumber());
}

void Polygon::setX1(int x1)
{
	Figure::setX1(x1);
	recalculatePointsFromCircumscribedRectangle();
}

void Polygon::setY1(int y1)
{
	Figure::setY1(y1);
	recalculatePointsFromCircumscribedRectangle();
}

void Polygon::setX2(int x2)
{
	Figure::setX2(x2);
	recalculatePointsFromCircumscribedRectangle();
}

void Polygon::setY2(int y2)
{
	Figure::setY2(y2);
	recalculatePointsFromCircumscribedRectangle();
}