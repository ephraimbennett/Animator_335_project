/**
 * @file Tubing.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_TUBING_H
#define CANADIANEXPERIENCE_MACHINELIB_TUBING_H

#include "Component.h"
#include "AirSource.h"
#include "AirSink.h"
#include "Clamp.h"

///A class for a tube
class Tubing : public Component
{
private:
	///point to begin at
	wxPoint mBegin;

	///point to end at
	wxPoint mEnd;

	///composite air source
	AirSource mAirSource;

	///composite air sink
	AirSink mAirSink;

	///vector of composite clamps
	std::vector<std::shared_ptr<Clamp>> mClamps;

	//drawing stuff
	///starting speed
	int mSpeedBegin = 100;

	///starting rotation
	double mStartingRotation = 0;

	///ending speed
	int mSpeedEnd = 50;

	///ending rotation
	double mEndingRotation = 0;

	///added to all speeds
	int mPressureIncrease = 0;

	void DrawBezier(wxPoint a, wxPoint b, double r1, int speed1, double r2, int speed2,
					std::shared_ptr<wxGraphicsContext>);

public:
	Tubing(std::wstring resourcesDir, int id);

	void Pressurize(double pressure);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void Update(double time) override;

	void SetTarget(AirSink * target);

	/**
	 * Gets a pointer to the Air Sink
	 * @return what do you think
	 */
	AirSink * GetSink() {return &mAirSink;}

	/**
	 * Gets a pointer to the Air Source
	 * @return
	 */
	AirSource * GetSource() {return &mAirSource;}

	/**
	 * Get the beginning point
	 * @return
	 */
	wxPoint GetBegin() {return mBegin;}

	/**
	 * Set the beginning point
	 * @param begin
	 */
	void SetBegin(wxPoint begin) {mBegin = begin;}

	/**
	 * Get the end point
	 * @return
	 */
	wxPoint GetEnd() {return mEnd;}

	/**
	 * Sets the end point
	 * @param end
	 */
	void SetEnd(wxPoint end) {mEnd = end;}

	/**
	 * Sets the beginning speed
	 * @param speed
	 */
	void SetBeginningSpeed(int speed) {mSpeedBegin = speed;}

	/**
	 * Sets the end rotation
	 * @param r
	 */
	void SetEndRotation(double r) {mEndingRotation = r;}


	void AddClamp(std::shared_ptr<Clamp> clamp);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_TUBING_H
