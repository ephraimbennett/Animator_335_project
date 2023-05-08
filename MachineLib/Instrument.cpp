/**
 * @file Instrument.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Instrument.h"

/**
 * Constructor
 * @param resourcesDir
 * @param engine
 * @param id
 */
Instrument::Instrument(std::wstring resourcesDir, ma_engine* engine, int id) : Shape(resourcesDir), mID(id),
mEngine(engine)
{
	//specify which audio file to use
	std::wstring result = mResourcesDir + L"/audio/";
	if (mID == 0)
	{
		result += L"organA4.wav";
	} else if (mID == 1)
	{
		result += L"organG4.wav";
	} else if (mID == 2)
	{
		result += L"organE4.wav";
	} else if (mID == 3)
	{
		result += L"organD4.wav";
	} else if (mID == 4)
	{
		result += L"organC4.wav";
	} else if (mID == 8)
	{
		result += L"kick.wav";
	} else if (mID == 9)
	{
		result += L"cymbal.wav";
	}
	mAudioPath = result;

	//set up the audio member variable
	auto res = ma_sound_init_from_file(engine, wxString(mAudioPath), 0, NULL, NULL, &mSound);
	if (res != MA_SUCCESS)
	{
		wxString msg;
		msg.Printf(L"Unable to load audio file %s - %d", mAudioPath, result);
		wxMessageBox( msg, wxT("miniaudio failure"), wxICON_ERROR);
	}
}

/**
 * Override the draw function
 * @param graphics
 */
void Instrument::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	Shape::Draw(graphics);
}

/**
 * Override the update function
 * @param time
 */
void Instrument::Update(double time)
{

}

/**
 * Function to play a specific sound.
 * Ideally, this will be upcalled by the specific type of instrument and supply the sound file.
 * Didn't decide to do that, determined sound through the ID
 */
void Instrument::PlaySound()
{
	mIsPlaying = true;
	// If the sound is already playing, stop it first
	if(ma_sound_is_playing(&mSound))
	{
		ma_sound_stop(&mSound);
	}

	// Always rewind to the beginning before playing
	ma_sound_seek_to_pcm_frame(&mSound, 0);

	// And play the sound!
	ma_sound_start(&mSound);
}

/**
 * stops the instrument from playing
 */
void Instrument::StopPlaying()
{
	mIsPlaying = false;
}

/**
 * Destructor
 */
Instrument::~Instrument()
{
	if(ma_sound_is_playing(&mSound))
	{
		ma_sound_stop(&mSound);
	}

	ma_sound_uninit(&mSound);
}