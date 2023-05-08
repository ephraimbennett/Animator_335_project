/**
 * @file Tubing.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Tubing.h"
#include "Machine.h"

/**
 * Constructor
 * @param resourcesDir
 * @param id
 */
Tubing::Tubing(std::wstring resourcesDir, int id) : Component(resourcesDir), mAirSink(), mAirSource(id)
{
}

/**
 * Draws this hoe
 * @param graphics
 */
void Tubing::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	if (mClamps.size() != 0)
	{
		//beginning to first clamp
		DrawBezier(mBegin, mClamps.at(0)->GetPosition(), mStartingRotation, mSpeedBegin,
				   mClamps.at(0)->GetRotation(), mClamps.at(0)->GetSpeed(), graphics);

		//last clamp to end
		auto lastClamp = mClamps.at(mClamps.size() - 1);
		DrawBezier(lastClamp->GetPosition(), mEnd, lastClamp->GetRotation(), lastClamp->GetSpeed(), mEndingRotation,
				   mSpeedEnd, graphics);
	} else {
		DrawBezier(mBegin, mEnd, mStartingRotation, mSpeedBegin, mStartingRotation, mSpeedEnd, graphics);
	}

}

/**
 * Draws a bezier curve between two points
 * @param a - the beginning point
 * @param b - the end point
 * @param r1 - rotation of point a
 * @param speed1 point a speed
 * @param r2 - rotation of point b
 * @param speed2 - speed of point b
 * @param graphics - obvious
 */
void Tubing::DrawBezier(wxPoint a, wxPoint b, double r1, int speed1, double r2, int speed2,
						std::shared_ptr<wxGraphicsContext> graphics)
{
	//set up the points
	auto machX = GetMachine()->GetPosition().x;
	auto machY = GetMachine()->GetPosition().y;

	//account for pressure
	speed1 += mPressureIncrease;
	speed2 += mPressureIncrease;

	wxPoint realBegin(a.x + machX, a.y + machY);
	wxPoint realEnd(b.x + machX, b.y + machY);

	auto p2x = realBegin.x - sin(r1 * M_PI * 2) * speed1;
	auto p2y = realBegin.y + cos(r1 * M_PI * 2) * speed1;
	wxPoint p2(p2x, p2y);

	//probably going to have to fix this
	auto p3x = realEnd.x - sin((r2 - 0.5) * M_PI * 2) * speed2;
	auto p3y = realEnd.y - cos((r2 - 0.5) * M_PI * 2) * speed2;
	wxPoint p3(p3x, p3y);

	wxPen pen(*wxBLACK, 3);

	graphics->SetPen(pen);
	graphics->PushState();
	auto path = graphics->CreatePath();
	path.MoveToPoint(realBegin);
	path.AddCurveToPoint(p2, p3, realEnd);
	graphics->StrokePath(path);
	graphics->PopState();
}

/**
 * Override implementation of update
 * @param time
 */
void Tubing::Update(double time)
{
	Pressurize(mAirSink.GetPressure());
}

/**
 * Add air pressure to this tube
 * @param pressure
 */
void Tubing::Pressurize(double pressure)
{
	mAirSource.Pressurize(pressure);
	if (mPressureIncrease < 10.0)
	{
		mPressureIncrease = static_cast<int>(pressure / 2);
	} else if (mPressureIncrease > 0) {
		mPressureIncrease = -static_cast<int>(pressure / 2);
	}
}

/**
 * Sets the target for our source
 * @param target
 */
void Tubing::SetTarget(AirSink *target)
{
	mAirSource.SetSink(target);
}

/**
 * Adds a clamp to this tube
 * @param clamp
 */
void Tubing::AddClamp(std::shared_ptr<Clamp> clamp)
{
	mClamps.push_back(clamp);
}


