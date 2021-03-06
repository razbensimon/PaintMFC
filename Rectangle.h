#pragma once
#include "Figure.h"

namespace shapes
{
	class Rectangle : public Figure
	{
	public:
		Rectangle() : Figure() {}
		Rectangle(int x1, int y1, int x2, int y2, int penWidth, COLORREF color, COLORREF fillColor)
			: Figure(x1, y1, x2, y2, penWidth, color, fillColor) {}
		void draw(CDC* displayContext) const override;
		virtual json toJson() const override;
	};
}
