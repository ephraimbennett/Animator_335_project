/**
 * @file MachineDrawable.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "Timeline.h"

/**
 * Constructor
 * @param name
 * @param resourcesDir
 * @param audioEngine
 */
MachineDrawable::MachineDrawable(std::wstring &name, std::wstring resourcesDir, ma_engine* audioEngine) : Drawable(name)
{
	//create the machine
	MachineSystemFactory machineSystemFactory(resourcesDir, audioEngine);
	mSystem = machineSystemFactory.CreateMachineSystem();
}

/**
 * Set up draw for this
 * @param graphics
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

	auto currentFrame = mTimeline->GetCurrentFrame();
	//check start time
	if (currentFrame >= mTimeline->GetMachineStartTime())
	{
		mSystem->SetMachineFrame(currentFrame - mTimeline->GetMachineStartTime());
	}

	graphics->PushState();
	mSystem->DrawMachine(graphics);
	graphics->PopState();
}

/**
 * Set up da hit test
 * @param pos
 * @return true if it was hit
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
	return false;
}

/**
 * Upcall so that normal channel timeline associations are created that I don't remember how works.
 * But more importantly store a pointer to the timeline so we can get the frame.
 * @param timeline
 */
void MachineDrawable::SetTimeline(Timeline *timeline)
{
	mTimeline = timeline;
	mSystem->SetFrameRate(timeline->GetFrameRate());
	Drawable::SetTimeline(timeline);
}


/**
 * Sets the position of the machine
 * @param loc
 */
void MachineDrawable::SetPosition(wxPoint loc)
{
	mPosition = loc;
	mSystem->SetLocation(wxPoint(mPosition.x, mPosition.y));
}

/**
 * Brings up a dialog box to update the machine
 * @param parent
 */
void MachineDrawable::ShowDialog(wxWindow* parent)
{
	MachineDialog dlg(parent, mSystem);
	if (dlg.ShowModal() == wxID_OK)
	{
		mSystem->SetLocation(mPosition);
	}
}

/**
 * Sets the machine number for this system
 * called when loading from xml
 * @param num
 */
void MachineDrawable::SetMachineNumber(int num)
{
	mSystem->SetMachineNumber(num);
	mSystem->SetLocation(mPosition);
}


