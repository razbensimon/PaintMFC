#pragma once
#include "figure.h"
#include "FIGURES.h"

using namespace shapes;

class ShapesFactory
{
public:
	static Figure* createShape(FIGURES figureType, int x1, int y1, int x2, int y2, double penWidth, COLORREF color, COLORREF fillColor);
};
