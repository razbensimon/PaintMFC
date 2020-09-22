#pragma once
#include "Figure.h"

namespace shapes
{
	class Line : public Figure
	{
	public:
		Line() : Figure() {}
		Line(int x1, int y1, int x2, int y2, int penWidth, COLORREF color)
			: Figure(x1, y1, x2, y2, penWidth, color) {}
		void draw(CDC* displayContext) const override;
		json toJson() const override;
		virtual bool isContains(const POINT& point) override;
	};
}
