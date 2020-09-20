#pragma once
#include "Polygon.h"

namespace  shapes
{
	class Hexagon : public Polygon
	{
	public:
		Hexagon() : Polygon() {}
		Hexagon(int x1, int y1, int x2, int y2, int penWidth, COLORREF color, COLORREF fillColor)
			: Polygon(x1, y1, x2, y2, penWidth, color, fillColor)
		{
			setPointsNumber(6);
			Hexagon::recalculatePointsFromCircumscribedRectangle();
		}

		virtual void recalculatePointsFromCircumscribedRectangle() override;
		virtual json toJson() const override;
	};
}