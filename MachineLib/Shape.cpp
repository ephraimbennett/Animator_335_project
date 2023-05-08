/**
 * @file Shape.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Shape.h"
#include "Machine.h"

/**
 * Constructor that stores the path to resources directory - upcalls
 * @param dirPath
 */
Shape::Shape(std::wstring dirPath) : Component(dirPath)
{

}

/**
 * Determines if this shape is being hit on (pause)
 * @return
 */
bool Shape::HitTest()
{
	return false;
}

/**
 * Override implementation of draw
 * @param graphics
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	auto x = GetMachine()->GetPosition().x;
	auto y = GetMachine()->GetPosition().y;
	mPolygon.DrawPolygon(graphics, mPosition.x + x, mPosition.y + y);
}

/**
 * Override implementation of update
 * @param time
 */
void Shape::Update(double time)
{

	Component::Update(time);
}

/**
 * Sets the image for the shape and the polygon
 * @param filename
 */
void Shape::SetImage(std::wstring filename)
{
	mPolygon.SetImage(mResourcesDir + filename);
}

/**
 * Sets the rotation for this component and the polygon
 * @param rotation
 */
void Shape::SetRotation(double rotation)
{
	Component::SetRotation(rotation);
	mPolygon.SetRotation(rotation);
}

/**
 * Sets the shape to a rectangle - calls from composition
 * @param x
 * @param y
 * @param width
 * @param height
 */
void Shape::Rectangle(int x, int y, int width, int height)
{
	mPolygon.Rectangle(x, y, width, height);
}

/**
 * Sets the color - call to polygon
 * @param colour
 */
void Shape::SetColor(wxColour colour)
{
	mPolygon.SetColor(colour);
}

