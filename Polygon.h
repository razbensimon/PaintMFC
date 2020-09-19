#pragma once
#include "Figure.h"

using namespace  shapes;

namespace  shapes
{
	class Polygon : public Figure
	{

	protected:
		POINT* _points;
		int _pointsNumber;
		
		Polygon(int x1, int y1, int x2, int y2, double penWidth, COLORREF color, COLORREF fillColor)
			: Figure(x1, y1, x2, y2, penWidth, color, fillColor), _points(NULL), _pointsNumber(0)
		{	
		}		
	public:
		using Figure::Figure;
		Polygon() : Figure(), _points(NULL), _pointsNumber(0) {}		
		virtual ~Polygon() { delete[] _points; }
		virtual void draw(CDC* displayContext) const override;

		int getPointsNumber() const { return _pointsNumber; }
		void setPointsNumber(int num) { _pointsNumber = num; }

		POINT* getPoints() const { return _points; }
		void setPoints(POINT* points) { _points = points; }

		virtual void setX1(int x1) override;
		virtual void setY1(int y1) override;
		virtual void setX2(int x2) override;
		virtual void setY2(int y2) override;

		virtual void recalculatePointsFromCircumscribedRectangle() = 0;
	};
}

