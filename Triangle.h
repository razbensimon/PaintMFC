#pragma once
#include "Polygon.h"

using namespace shapes;

namespace  shapes
{
	class Triangle : public Polygon
	{
	public:
		Triangle() : Polygon() {}
		Triangle(int x1, int y1, int x2, int y2, double penWidth, COLORREF color, COLORREF fillColor)
			: Polygon(x1, y1, x2, y2, penWidth, color, fillColor)
		{
			setPointsNumber(3);
			Triangle::recalculatePointsFromCircumscribedRectangle();
		}

		virtual void recalculatePointsFromCircumscribedRectangle() override;
	};
}

