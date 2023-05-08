/**
 * @file MachineDrawable.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include "Drawable.h"
#include "MainFrame.h"
#include <machine-api.h>

///The machine drawable class that inherits from drawable whoa
class MachineDrawable : public Drawable
{
private:
	///start time
	double mStartTime = 0.0;

	///the machine system
	std::shared_ptr<MachineSystem> mSystem;

	///pointer to the timeline
	Timeline * mTimeline;

	///this drawables position
	wxPoint mPosition;
public:

	MachineDrawable(std::wstring & name, std::wstring resourcesDir, ma_engine* audioEngine);
	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	bool HitTest(wxPoint pos) override;

	void SetTimeline(Timeline * timeline);

	void SetPosition(wxPoint loc) override;

	void ShowDialog(wxWindow* parent) override;

	/**
	 * Gets the machine number being drawn
	 * @return
	 */
	int GetMachineNumber() {return mSystem->GetMachineNumber();}

	void SetMachineNumber(int num);


};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
