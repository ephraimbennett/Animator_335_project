/**
 * @file AirSink.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H

#include "Component.h"

///forward references
class AirSource;

///AirSink class
class AirSink
{
private:
	///the pressure received by this air sink
	double mPressure = 0.0;

	///association to the source
	AirSource * mSource;

public:
	AirSink();

	void Pressurize(double pressure);

	void SetSource(AirSource * source);

	/**
	 * Gets the pressure of air that is in this sink at the current moment
	 * @return
	 */
	double GetPressure() {return mPressure;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H