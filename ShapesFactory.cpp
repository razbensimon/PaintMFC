#include "pch.h"
#include "ShapesFactory.h"
#include "FIGURES.h"
#include "Figure.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"

using namespace shapes;

Figure* ShapesFactory::createShape(FIGURES figureType, int x1, int y1, int x2, int y2, double penWidth, COLORREF color, COLORREF fillColor)
{
	switch (figureType)
	{
	default:
	case RECTANGLE:
		return new shapes::Rectangle(x1, y1, x2, y2, penWidth, color, fillColor);
	case ELLIPSE:
		return new shapes::Ellipse(x1, y1, x2, y2, penWidth, color, fillColor);
	case TRIANGLE:
		return new Triangle(x1, y1, x2, y2, penWidth, color, fillColor);
	}
}

Figure* ShapesFactory::createShape(json figure)
{
	const auto type = figure["type"].get<FIGURES>();
	const auto x1 = figure["x1"].get<int>();
	const auto y1 = figure["y1"].get<int>();
	const auto x2 = figure["x2"].get<int>();
	const auto y2 = figure["y2"].get<int>();
	const auto penWidth = figure["penWidth"].get<double>();
	const auto color = figure["color"].get<COLORREF>();
	const auto fillColor = figure["fillColor"].get<COLORREF>();

	return createShape(type, x1, y1, x2, y2, penWidth, color, fillColor);
}
