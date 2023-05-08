/**
 * @file CardReader.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H
#define CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H

#include "Component.h"
#include "Polygon.h"
#include "AirSource.h"

///CardReader class
class CardReader : public Component
{
private:

	///the beats per minute for this card reader
	double mBeatsPerMin = 180;

	///the column we are reading
	int mColumn = 0;

	///path for the card
	std::wstring mCardPath;

	///composite polygon for the front image
	cse335::Polygon mFront;

	///composite polygon for the back image
	cse335::Polygon mBack;

	///composite polygon for the card itself
	cse335::Polygon mCard;

	///vector of Air source compositions
	std::vector<std::shared_ptr<AirSource>> mAirSources;

	///indicates if the card reader is done
	bool mIsDone = false;

public:

	CardReader(std::wstring resourcesPath);

	/**
	 * Getter for bpm
	 * @return
	 */
	double GetBeatsPerMin() {return mBeatsPerMin;}

	/**
	 * Setter for bpm
	 * @param bpm double
	 */
	void SetBeatsPerMin(double bpm) {mBeatsPerMin = bpm;}

	void SetCardPath(std::wstring path);

	void SetSink(AirSink *sink, int id);

	void Pressurize(double pressure, int row);

	bool IsPunched(int column, int row);

	/**
	 * Getter for the width
	 * @return
	 */
	int GetWidth() {return mBack.GetImageWidth();}

	/**
	 * Getter for the height
	 * @return
	 */
	int GetHeight() {return mBack.GetImageHeight();}

	/**
	 * Gets a specific air source
	 * @param id
	 * @return
	 */
	std::shared_ptr<AirSource> GetAirSource(int id) {return mAirSources.at(id);}

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	void Update(double time) override;

	void SetAirSources();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H
