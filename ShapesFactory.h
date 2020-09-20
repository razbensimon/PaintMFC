#pragma once
#include "Figure.h"
#include "FIGURES.h"
#include "json.hpp"

using namespace shapes;
using json  = nlohmann::json;

class ShapesFactory
{
public:
	static Figure* createShape(FIGURES figureType, int x1, int y1, int x2, int y2, int penWidth, COLORREF color, COLORREF fillColor);
	static Figure* createShape(json figure); // Deserialize
};
