/**
 * @file Cylinder.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H
#define CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H

#include "Component.h"
#include "Polygon.h"
#include "AirSink.h"

///forward reference
class StruckInstrument;

///Cylinder class
class Cylinder : public Component
{
private:
	///composite polygon for the base
	cse335::Polygon mBase;

	///composite polygon for the actual cylinder
	cse335::Polygon mCylinder;

	///composite polygon for the ram
	cse335::Polygon mRam;

	///composite Air Sink
	AirSink mSink;

	///association to a struck instrument
	std::shared_ptr<StruckInstrument> mStruckInstrument;

	///indicates if we are in the process of striking
	bool mIsStriking = false;

public:
	Cylinder(std::wstring resourcesDir);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void Update(double time) override;

	/**
	 * Gets a pointer to the air sink
	 * @return ptr
	 */
	AirSink * GetSink() {return &mSink;}

	void SetRotation(double rotation);

	void SetInstrument(std::shared_ptr<StruckInstrument> instrument);

	void Strike();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H
