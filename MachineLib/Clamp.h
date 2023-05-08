/**
 * @file Clamp.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CLAMP_H
#define CANADIANEXPERIENCE_MACHINELIB_CLAMP_H

///Clamp class
class Clamp
{
private:
	///position
	wxPoint mPosition;

	///rotation of air
	double mRotation = 0;

	///speed of air
	int mSpeed = 50;
public:
	Clamp(wxPoint pos, double rot, int speed);

	/**
	 * Gets position
	 * @return
	 */
	wxPoint GetPosition() {return mPosition;}

	/**
	 * Gets rotation
	 * @return
	 */
	double GetRotation() {return mRotation;}

	/**
	 * Gets the speed
	 * @return
	 */
	int GetSpeed() {return mSpeed;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CLAMP_H
