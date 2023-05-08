/**
 * @file StruckInstrument.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H
#define CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H

#include "Instrument.h"
#include <miniaudio.h>

///forward reference
class Cylinder;

///The struck instrument class
class StruckInstrument : public Instrument
{
private:
	///association to a cylinder
	Cylinder * mCylinder;

public:
	StruckInstrument(std::wstring resourcesDir, ma_engine*, int id);

	virtual void Strike(bool flag);

	/**
	 * Sets the cylinder for this struck instrument
	 * @param cyl
	 */
	void SetCylinder(Cylinder* cyl) {mCylinder = cyl;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H
