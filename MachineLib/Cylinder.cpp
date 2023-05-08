/**
 * @file Cylinder.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Cylinder.h"
#include "Machine.h"
#include "StruckInstrument.h"
#include <cstdlib>

///path to base image
const std::wstring CylinderBaseImage = L"/images/cylinder-base.png";

///path to cylinder image
const std::wstring CylinderImage = L"/images/cylinder.png";

///path to the cyldiner ram
const std::wstring CylinderRamImage = L"/images/cylinder-ram.png";

///the strike offset
const int StrikeOffset = 30;

/**
 * Constructor
 * @param resourcesDir
 */
Cylinder::Cylinder(std::wstring resourcesDir) : Component(resourcesDir)
{
	//init the base, bottom centered on component's x location
	mBase.SetImage(mResourcesDir + CylinderBaseImage);
	mBase.Rectangle(-mBase.GetImageWidth() / 2, 0);

	//init the cylinder
	mCylinder.SetImage(mResourcesDir + CylinderImage);
	mCylinder.Rectangle(-mCylinder.GetImageWidth() / 2, 0);

	//init the ram
	mRam.SetImage(mResourcesDir + CylinderRamImage);
	mRam.Rectangle(-mRam.GetImageWidth() / 2, 0);
}

/**
 * Override draw function
 * @param graphics
 */
void Cylinder::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	auto x = GetMachine()->GetPosition().x;
	auto y = GetMachine()->GetPosition().y;

	//first, draw the base
	mBase.DrawPolygon(graphics, x + GetPosition().x,y + GetPosition().y);

	//ram is second because it needs to be "inside" the cylinder
	if (mIsStriking)
	{
		//first, we need to convert back into radians
		//we also add pi/2, because we only care about the perpendicular angle because that is the direction the
		//ram actually moves in
		auto theta = mRam.GetRotation() * M_PI * 2.0 + (M_PI / 2.0);
		int realOffsetX = -StrikeOffset * cos(theta);
		int realOffsetY = StrikeOffset * sin(theta);
		mRam.DrawPolygon(graphics, GetPosition().x + x + realOffsetX, GetPosition().y + y - realOffsetY);
	}
	else
	{
		mRam.DrawPolygon(graphics, GetPosition().x + x, GetPosition().y + y);
	}

	//cylinder is drawn last
	mCylinder.DrawPolygon(graphics, GetPosition().x + x, GetPosition().y + y);
}

/**
 * Override update function
 * @param time
 */
void Cylinder::Update(double time)
{
	if (mSink.GetPressure() > 10 && !mIsStriking)
	{
		mIsStriking = true;
		mStruckInstrument->Strike(mIsStriking);
	}
	else if (mSink.GetPressure() < 10)
	{
		mIsStriking = false;
	}
}

/**
 * Strikes the instrument
 */
void Cylinder::Strike()
{
	mIsStriking = true;
}

/**
 * Override rotation function
 * @param rotation
 */
void Cylinder::SetRotation(double rotation)
{
	Component::SetRotation(rotation);
	mBase.SetRotation(mOrientation);
	mCylinder.SetRotation(mOrientation);
	mRam.SetRotation(mOrientation);
}

/**
 * Sets the instrument for this cylinder.
 * Creates the corresponding association for the instrument as well
 * @param instrument
 */
void Cylinder::SetInstrument(std::shared_ptr<StruckInstrument> instrument)
{
	mStruckInstrument = instrument;
	mStruckInstrument->SetCylinder(this);
}
