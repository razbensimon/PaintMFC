#pragma once
#include "Figure.h"

namespace shapes
{
	class Ellipse : public Figure
	{
	public:		
		Ellipse() : Figure() {}
		Ellipse(int x1, int y1, int x2, int y2, int penWidth, COLORREF color, COLORREF fillColor)
			: Figure(x1, y1, x2, y2, penWidth, color, fillColor) {}
		virtual void draw(CDC* displayContext) const override;
		virtual json toJson() const override;		
	};
}
