/**
 * @file AirSource.h
 * @author Ephraim Bennnett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H


///forward references
class AirSink;

///AirSource class
class AirSource
{
private:
	///level of pressure to create
	double mPressure = 0.0;

	///id will indicate which tube and air sink we are connecting to
	int mID;

	///association to an air sink
	AirSink* mAirSink;

	///indicates if this source is actually connected to a sink. Class does nothing if false
	bool mEnabled = true;

	///optional location (for tubing purposes)
	wxPoint mLocation;

public:
	AirSource(int id);

	void Pressurize(double pressure);

	void SetSink(AirSink * sink);

	/**
	 * Disables this air source
	 */
	void Disable() {mEnabled = false;}

	/**
	 * Getter for location
	 * @return
	 */
	wxPoint GetLocation(){return mLocation;}

	/**
	 * Setter for location
	 * @param loc
	 */
	void SetLocation(wxPoint loc) {mLocation = loc;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H
