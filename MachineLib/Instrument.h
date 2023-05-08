/**
 * @file Instrument.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H
#define CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H

#include "Shape.h"
#include <miniaudio.h>

///Instrument class
class Instrument : public Shape
{
private:
	///id of the instrument will indicate which audio is to be played
	int mID = -1;

	///the string path to the audio
	std::wstring mAudioPath;

	///the audio engine
	ma_engine* mEngine;

	/// The miniaudio sound
	ma_sound mSound;

	///indicates if this instrument should be playing
	bool mIsPlaying = false;



public:
	Instrument(std::wstring resourcesDir, ma_engine*, int id);

	~Instrument();

	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	virtual void Update(double time) override;

	void PlaySound();
	void StopPlaying();

	/**
	 * Indicates if the instrument is playing
	 * @return
	 */
	bool IsPlaying() {return mIsPlaying;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H
