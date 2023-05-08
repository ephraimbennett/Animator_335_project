/**
 * @file Cymbal.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Cymbal.h"
#include "Machine.h"

///the image path for the entire cymbal
const std::wstring CymbalImagePath = L"/images/cymbal-all.png";

/// File name for the cymbal stand
const std::wstring CymbalStandFilename = L"/images/cymbal-stand.png";

/// File name for the cymbal image
const std::wstring CymbalFileName = L"/images/cymbal.png";

/// Offset to the center of the cymbal from the left in pixels
const int CymbalCenterX = 57;

/// Offset to the center of the cymbal from the bottom in pixels
const int CymbalCenterY = 36;

/// X Location to place the cymbal relative to the stand
const int CymbalPlaceX = 0;

/// Y location to place the cymbal relative to the stand
const double CymbalPlaceY = -205;

/// How long the rocking lasts in seconds
const double RockingTime = 2.0;

/// Maximum amount to rock in unit rotations
const double RockAmount = 0.03;

/// How quickly to rock in radians per second
const double RockRate = M_PI * 4;

/**
 * Constructor
 * @param resourcesDir
 * @param engine
 * @param id
 */
Cymbal::Cymbal(std::wstring resourcesDir, ma_engine *engine, int id) : StruckInstrument(resourcesDir, engine, id)
{
	//set up the polygons
	mStand.SetImage(mResourcesDir + CymbalStandFilename);
	mCymbal.SetImage(mResourcesDir + CymbalFileName);
}

/**
 * Override implementation of draw
 * @param graphics
 */
void Cymbal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	auto x = GetMachine()->GetPosition().x;
	auto y = GetMachine()->GetPosition().y;

	mStand.DrawPolygon(graphics, x , y);

	graphics->PushState();
	graphics->Translate(x + GetPosition().x + CymbalCenterX, y + GetPosition().y - CymbalCenterY);
	graphics->Rotate(mCymbalRotation);

	mCymbal.DrawPolygon(graphics,  -CymbalCenterX, CymbalCenterY);
	graphics->PopState();
}

/**
 * Override implementation of update
 * @param time
 */
void Cymbal::Update(double time)
{
	if (mIsRocking)
	{
		if (mRockStartTime < 0)
		{
			mRockStartTime = time;// if this is the first time, store it
			mLastTime = time;
		}

		double elapsed = time - mLastTime;
		if (time - mRockStartTime > 2.0)//after two seconds, end
		{
			mRockStartTime = -1.0;
			mIsRocking = false;
			mCymbalRotation = 0;
			return;
		}

		mCymbalRotation += elapsed / 2 * mDirection;
		if (mCymbalRotation > 0.15 || mCymbalRotation < -0.15)
		{
			mDirection = mDirection * -1.0;
		}
		mLastTime = time;
	}
}

/**
 * override implementation of strike to trigger
 * @param flag
 */
void Cymbal::Strike(bool flag)
{
	mIsRocking = true;
	mRockStartTime = -1.0;
	mCymbalRotation = 0;
	mDirection = 1.0;
	PlaySound();
}


/**
 * Sets the position of this cymbal
 * @param pos
 */
void Cymbal::SetPosition(wxPoint pos)
{
	mStand.Rectangle(pos.x, pos.y);
	mCymbal.Rectangle(0, 0);
	pos.y = pos.y - (mStand.GetImageHeight() - mCymbal.GetImageHeight());
//	pos.y = pos.y - CymbalCenterY;
//	pos.x = pos.x - CymbalCenterX;
	Shape::SetPosition(pos);
}

/**
 * Override to account for two polygons
 * @return stand height, since it's technically the same as the original cymbal image
 */
int Cymbal::GetImageHeight()
{
	return mStand.GetImageHeight();
}
/**
 * Override for same reasons as height
 * @return the stand width, since it's technically the same
 */
int Cymbal::GetImageWidth()
{
	return mStand.GetImageWidth();
}
