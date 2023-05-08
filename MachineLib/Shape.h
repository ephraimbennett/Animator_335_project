/**
 * @file Shape.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SHAPE_H
#define CANADIANEXPERIENCE_MACHINELIB_SHAPE_H

#include "Component.h"
#include "Polygon.h"

///The shape class
class Shape : public Component
{
private:
	///the polygon for this shape
	cse335::Polygon mPolygon;

	///shape's origin
	wxPoint mOrigin;

public:
	Shape(std::wstring dirPath);

	//getters and setters
	/**
	 * Getter for the origin
	 * @return
	 */
	wxPoint GetOrigin() {return mOrigin;}

	/**
	 * Setter for the origin
	 * @param origin
	 */
	void SetOrigin(wxPoint origin){mOrigin = origin;}

	//other functions

	bool HitTest();

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	void Update(double time);

	void SetImage(std::wstring filename);

	void SetRotation(double rotation) override;

	void Rectangle(int x, int y, int width = 0, int height = 0);

	void SetColor(wxColour colour);

	/**
	 * Gets image width
	 * @return the width
	 */
	virtual int GetImageWidth() {return mPolygon.GetImageWidth();}

	/**
	 * Gets the image height
	 * @return the height
	 */
	virtual int GetImageHeight() {return mPolygon.GetImageHeight();}


};

#endif //CANADIANEXPERIENCE_MACHINELIB_SHAPE_H
