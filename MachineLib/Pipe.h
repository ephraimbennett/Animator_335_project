/**
 * @file Pipe.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PIPE_H
#define CANADIANEXPERIENCE_MACHINELIB_PIPE_H

#include "Instrument.h"
#include "AirSink.h"
#include "Tubing.h"

///The pipe class
class Pipe : public Instrument
{
private:
	///height of the pipe
	int mHeight = 0;

	///composition air sink
	AirSink mAirSink;

	///composite polygon for the base of the pipe
	cse335::Polygon mBase;

	///composite polygon for the body of the pipe
	cse335::Polygon mBody;

	///composite polygon for the top of the pipe
	cse335::Polygon mTop;

	///composite polygon for the puffer
	cse335::Polygon mPuff;

public:
	Pipe(std::wstring resourcesDir, ma_engine* engine, int id, int height);

	//getter and setter
	/**
	 * Gets the height
	 * @return
	 */
	int GetHeight() {return mHeight;}

	/**
	 * Sets the height
	 * @param height
	 */
	void SetHeight(int height) {mHeight = height;}

	void Actuate(double pressure);

	/**
	 * Gets the composite air sink of the pipe. Returns a pointer not the actual thing duh
	 * @return
	 */
	AirSink * GetSink() {return &mAirSink;}

	void ConnectTube(std::shared_ptr<Tubing>);

	void Update(double time) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PIPE_H
