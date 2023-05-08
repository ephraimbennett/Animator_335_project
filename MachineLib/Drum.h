/**
 * @file Drum.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_DRUM_H
#define CANADIANEXPERIENCE_MACHINELIB_DRUM_H

#include "StruckInstrument.h"

///Drum class
class Drum : public StruckInstrument
{
private:

public:
	Drum(std::wstring resourcesDir, ma_engine* engine, int id);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
	void Update(double time) override;

	void SetRotation(double rotation) override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_DRUM_H
