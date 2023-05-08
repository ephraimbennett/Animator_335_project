/**
 * @file AirSource.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "AirSource.h"
#include "AirSink.h"

/**
 * Constructor
 * @param id
 */
AirSource::AirSource(int id)
{
	mID = id;
}

/**
 * Send pressure through this air source
 * @param pressure
 */
void AirSource::Pressurize(double pressure)
{
	if (!mEnabled) return;
	mPressure = pressure;
	mAirSink->Pressurize(pressure);
}

/**
 * Sets the air sink that this source is supposed to route to
 * @param sink
 */
void AirSource::SetSink(AirSink * sink)
{
	mAirSink = sink;
	sink->SetSource(this);
}
