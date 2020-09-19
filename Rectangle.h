#pragma once
#include "Figure.h"

namespace shapes
{
	class Rectangle : public Figure
	{
	public:
		Rectangle() : Figure() {}
		Rectangle(int x1, int y1, int x2, int y2, double penWidth, COLORREF color)
			: Figure(x1, y1, x2, y2, penWidth, color) {}
		void draw(CDC* displayContext) const override;
	};
}