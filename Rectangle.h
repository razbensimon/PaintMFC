#pragma once
#include "Figure.h"

class Rectangle : public Figure
{
public:
	void draw(CDC* displayContext) const override;
};