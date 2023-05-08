/**
 * @file AirSink.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "AirSink.h"
#include "AirSource.h"

AirSink::AirSink()
{

}

/**
 * Pressurize this air sink
 * @param pressure
 */
void AirSink::Pressurize(double pressure)
{
	mPressure = pressure;
}

/**
 * Set the source for this sink
 * @param source
 */
void AirSink::SetSource(AirSource * source)
{
	mSource = source;
}
