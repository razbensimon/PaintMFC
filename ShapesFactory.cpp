#include "pch.h"
#include "ShapesFactory.h"
#include "FIGURES.h"
#include "Figure.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "Line.h"

using namespace shapes;

Figure* ShapesFactory::createShape(FIGURES figureType, int x1, int y1, int x2, int y2, int penWidth, COLORREF color, COLORREF fillColor)
{
	switch (figureType)
	{
	default:
	case FIGURES::RECTANGLE:
		return new shapes::Rectangle(x1, y1, x2, y2, penWidth, color, fillColor);
	case FIGURES::ELLIPSE:
		return new shapes::Ellipse(x1, y1, x2, y2, penWidth, color, fillColor);
	case FIGURES::TRIANGLE:
		return new Triangle(x1, y1, x2, y2, penWidth, color, fillColor);
	case FIGURES::LINE:
		return new Line(x1, y1, x2, y2, penWidth, color);
	}
}

Figure* ShapesFactory::createShape(json figure) // Deserialize
{
	const auto type = figure["type"].get<FIGURES>();
	const auto x1 = figure["x1"].get<int>();
	const auto y1 = figure["y1"].get<int>();
	const auto x2 = figure["x2"].get<int>();
	const auto y2 = figure["y2"].get<int>();
	const auto penWidth = figure["penWidth"].get<int>();
	const auto color = figure["color"].get<COLORREF>();
	const auto fillColor = figure["fillColor"].get<COLORREF>();

	return createShape(type, x1, y1, x2, y2, penWidth, color, fillColor);
}
