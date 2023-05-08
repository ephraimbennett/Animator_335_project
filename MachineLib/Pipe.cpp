/**
 * @file Pipe.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Pipe.h"
#include "Machine.h"

/// The pipe base image
const std::wstring PipeBaseImage = L"/images/pipe-base.png";

/// The pipe image
const std::wstring PipeImage = L"/images/pipe.png";

/// The pipe top image
const std::wstring PipeTopImage = L"/images/pipe-top.png";

/// The pipe puff image
const std::wstring PuffImage = L"/images/puff.png";

/// Pipe images width in pixels
const int PipeWidth = 20;

/// Pipe base height
const int PipeBaseHeight = 20;

/// Puff image width in pixel
const int PuffWidth = 65;

/**
 * Constructor
 * @param resourcesDir
 * @param engine
 * @param id
 * @param height
 */
Pipe::Pipe(std::wstring resourcesDir, ma_engine* engine, int id, int height) : Instrument(resourcesDir, engine, id),
mHeight(height)
{
	//the first thing we need to do is draw the base. Pipe bottom centered on component's location
	mBase.SetImage(mResourcesDir + PipeBaseImage);
	mBase.Rectangle(-PipeWidth / 2, 0, PipeWidth, PipeBaseHeight);

	//set up the body
	mBody.SetImage(mResourcesDir + PipeImage);
	mBody.Rectangle(-PipeWidth / 2, -PipeBaseHeight, PipeWidth, mHeight);

	//set up the top
	mTop.SetImage(mResourcesDir + PipeTopImage);
	mTop.Rectangle(-PipeWidth / 2, (-PipeBaseHeight - mHeight), PipeWidth);

	//set up the puffer
	mPuff.SetImage(mResourcesDir + PuffImage);
	mPuff.Rectangle(-PuffWidth / 2, (-PipeBaseHeight - mHeight), PuffWidth);
}

/**
 * Override for pipe's own version of update whaaat
 * @param time
 */
void Pipe::Update(double time)
{
	//if it is pressurized and not already playing
	if (mAirSink.GetPressure() >= 10 && !IsPlaying())
	{
		PlaySound();
	}
	//if it is playing and not pressurized
	else if (IsPlaying() && mAirSink.GetPressure() < 10)
	{
		StopPlaying();
	}
}

/**
 * Override for pipe's own version of draw
 * @param graphics
 */
void Pipe::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	auto x = GetMachine()->GetPosition().x;
	auto y = GetMachine()->GetPosition().y;

	mBase.DrawPolygon(graphics, mPosition.x + x, mPosition.y + y);
	mBody.DrawPolygon(graphics, mPosition.x + x, mPosition.y + y);
	mTop.DrawPolygon(graphics, mPosition.x + x, mPosition.y + y);

	//draw the puff if we are playing a sound
	if (IsPlaying())
	{
		mPuff.DrawPolygon(graphics, mPosition.x + x, mPosition.y + y);
	}
}

/**
 * Sets up proper connections between sinks and sources
 * @param tube
 */
void Pipe::ConnectTube(std::shared_ptr<Tubing> tube)
{
	tube->SetTarget(&mAirSink);
}

/**
 * Actuates or whatever the fuck that means
 * @param pressure
 */
void Pipe::Actuate(double pressure)
{

}
