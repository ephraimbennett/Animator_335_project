/**
 * @file CardReader.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "CardReader.h"
#include "Machine.h"


/// Image for the back of the card reader
const std::wstring CardReaderBackImage = L"/images/card-reader-back.png";

/// Image for the front of the card reader
const std::wstring CardReaderFrontImage = L"/images/card-reader-front.png";

/// Image for the basic card
const std::wstring CardImage = L"/images/card.png";

/// Width to draw the card on the screen in pixels
const int CardWidth = 132;

/// Height to draw the card on the screen in pixels
const int CardLength = 297;

/// Amount of offset the center of the card so it will
/// appear at the right place relative to the card reader.
const int CardOffsetX = 126;

/// Y dimension of the offset
const int CardOffsetY = 65;

// These values are all for the underlying image. They
// can be used for find the punches.

/// Width of a card column in pixels
const int CardColumnWidth = 10;

/// Height of a card row in pixels
const int CardRowHeight = 29;

/// X offset for the first column (left side)
const int CardColumn0X = 24;

/// Y offset to the first row (0's)
/// There are actually two rows above this that can be used
const int CardRow0Y = 78;

/// Width of a punched hole
const int CardPunchWidth = 8;

/// Height of a punched hole
const int CardPunchHit = 20;

/// Any average luminance below this level is considered a punched hole
const double CardPunchLuminance = 0.1;

/// the last column of the card
const int LastColumn = 80;

//for the air sources
///distance between leftmost side of card reader and the first air source
const int ReaderLeftPad = 38;

///distance between air sources
const int AirSourcePadding = 11;

///y distance the sources sit at
const int AirSourceYLoc = 93;


/**
 * Constructor that stores the path to the resources directory
 * @param resourcesPath
 */
CardReader::CardReader(std::wstring resourcesPath) : Component(resourcesPath)
{
	mBack.SetImage(mResourcesDir + CardReaderBackImage);
	mBack.Rectangle(-mBack.GetImageWidth() / 2, 0);

	mFront.SetImage(mResourcesDir + CardReaderFrontImage);
	mFront.Rectangle(-mFront.GetImageWidth() / 2, 0);

	mCard.SetImage(mResourcesDir + CardImage);
	mCard.Rectangle(CardOffsetX, CardOffsetY, CardLength, CardWidth);
	mCard.SetRotation(-0.25);

}

/**
 * Draws this card reader
 * @param graphics
 */
void CardReader::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	int x = GetMachine()->GetPosition().x;
	int y = GetMachine()->GetPosition().y;
	mBack.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);

	auto cardScale = (double)CardLength / mCard.GetImageWidth();
	if (mIsDone)
	{
		mCard.DrawPolygon(graphics, x + GetPosition().x, y + (LastColumn-1) * cardScale * CardColumnWidth);
	}
	else {
		mCard.DrawPolygon(graphics, x + GetPosition().x, y + (mColumn-1) * cardScale * CardColumnWidth);
	}

	mFront.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);


}

/**
 * Update override
 * Changes the column based upon beats or something
 * @param time
 */
void CardReader::Update(double time)
{

	int oldCol = mColumn;
	mColumn = time * mBeatsPerMin / 60.0;
	//check if we've reached the end of the column
	if (mColumn > 81)
	{
		mIsDone = true;
		return;
	}
	mIsDone = false;

	if (mColumn != oldCol) // on switch
	{
		for (int row = 0; row < 10; row++)
		{
			if (IsPunched(mColumn, row))
			{
				Pressurize(11.0, row);
			}
		}
	}
	else //in between notes
	{
		//determine if the air gap is still open
		double x = time * mBeatsPerMin / 60.0;
		if (x - static_cast<double>(mColumn) > 0.5)
		{
			for (int row = 0; row < 10; row++)
			{
				Pressurize(0.0, row);
			}
		}
	}

}

/**
* Sets the card path to read
* @param path
*/
void CardReader::SetCardPath(std::wstring path)
{
	mCardPath = path;
	mCard.SetImage(mResourcesDir + mCardPath);
}

/**
 * Pressurizes this card reader
 * Uses composite method from air source
 * @param pressure
 * @param row
 */
void CardReader::Pressurize(double pressure, int row)
{
	mAirSources.at(row)->Pressurize(pressure);
}

/**
 * Checks the card to see if this specific slot is punch or not
 * true indicates that it is punched. If its punched we let airflow through?
 * @param column
 * @param row
 * @return
 */
bool CardReader::IsPunched(int column, int row)
{
	auto luminance = mCard.AverageLuminance(CardColumn0X + (column - 1) * CardColumnWidth,
											CardRow0Y + CardRowHeight * row, CardPunchWidth, CardPunchHit);
	return luminance < CardPunchLuminance;
}

/**
 * Calls the composite function for our source to set its sink
 * @param sink
 * @param id
 */
void CardReader::SetSink(AirSink *sink, int id)
{
	mAirSources.at(id)->SetSink(sink);
}
/**
 * ONLY CALL AFTER READER HAS BEEN ADDED TO MACHINE
 * Sets up the air sources
 */
void CardReader::SetAirSources()
{
	//set up the air sources
	auto a = GetPosition().x;
	for (int i = 0; i < 10; i++)
	{
		auto airSource = std::make_shared<AirSource>(i);

		wxPoint loc((this->GetPosition().x - mFront.GetImageWidth() / 2) + ReaderLeftPad + AirSourcePadding * i,
					this->GetPosition().y - AirSourceYLoc);

		airSource->SetLocation(wxPoint(loc));
		auto x = airSource->GetLocation();
		mAirSources.push_back(airSource);
	}

	//disable sources 5-7
	for (int i = 5; i < 8; i++)
	{
		mAirSources.at(i)->Disable();
	}
}


