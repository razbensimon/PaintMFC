#include "pch.h"
#include "ShapesFactory.h"
#include "FIGURES.h"
#include "Figure.h"
#include "Rectangle.h"
#include "Triangle.h"

using namespace shapes;

Figure* ShapesFactory::createShape(FIGURES figureType, int x1, int y1, int x2, int y2, double penWidth, COLORREF color)
{
	switch (figureType)
	{
	case RECTANGLE:
		return new shapes::Rectangle(x1, y1, x2, y2, penWidth, color);
	case ELLIPSE:
		break;
	case TRIANGLE:
		return new Triangle(x1, y1, x2, y2, penWidth, color);
	}
}
