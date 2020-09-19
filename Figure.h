#pragma once

const COLORREF BLACK = 0x00000000;

namespace shapes
{
	class Figure
	{
	protected:
		int _x1;
		int _y1;
		int _x2;
		int _y2;
		double _penWidth;
		COLORREF _penColor;
	public:
		virtual ~Figure() {}
		Figure(int x1, int y1, int x2, int y2, double penWidth = 10.0, COLORREF color = BLACK) {
			this->_x1 = x1;
			this->_y1 = y1;
			this->_x2 = x2;
			this->_y2 = y2;
			this->_penWidth = penWidth;
			this->_penColor = color;
		}

		Figure() : Figure(0, 0, 0, 0)
		{
		}

		virtual int getX1() const { return this->_x1; }
		virtual int getY1() const { return this->_y1; }
		virtual int getX2() const { return this->_x2; }
		virtual int getY2() const { return this->_y2; }
		virtual void setX1(int x1) { this->_x1 = x1; }
		virtual void setY1(int y1) { this->_y1 = y1; }
		virtual void setX2(int x2) { this->_x2 = x2; }
		virtual void setY2(int y2) { this->_y2 = y2; }

		COLORREF getColor() const { return this->_penColor; }
		double getPenWidth() const { return this->_penWidth; }
		void setColor(COLORREF color) { this->_penColor = color; }
		void setPenWidth(double width) { this->_penWidth = width; }

		virtual void draw(CDC* displayContext) const = 0;
	};

}