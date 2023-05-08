/**
 * @file Cymbal.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CYMBAL_H
#define CANADIANEXPERIENCE_MACHINELIB_CYMBAL_H

#include "StruckInstrument.h"

///Cymbal class
class Cymbal : public StruckInstrument
{
private:
	///composite polygon for the stand
	cse335::Polygon mStand;

	///composite polygon for the actual cymbal
	cse335::Polygon mCymbal;

	///store the rotation of the cymbal
	double mCymbalRotation = 0;

	///indicates if we are rocking
	bool mIsRocking = false;

	///stores the time when the last strike was
	double mRockStartTime = -1.0;

	///stores the last time
	double mLastTime = -1.0;

	///indicates which direction we're turning
	double mDirection = 1;

public:
	Cymbal(std::wstring resourcesDir, ma_engine* engine, int id);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void Update(double time) override;

	void Strike(bool flag) override;

	void SetPosition(wxPoint pos) override;

	int GetImageHeight() override;
	int GetImageWidth() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CYMBAL_H
