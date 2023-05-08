/**
 * @file TimelineDlg.h
 * @author Charles Owen
 *
 * Timeline dialog box
 */

#ifndef CANADIANEXPERIENCE_TIMELINEDLG_H
#define CANADIANEXPERIENCE_TIMELINEDLG_H

class Timeline;

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
    void OnOK(wxCommandEvent& event);

    /// The pointer to the Timeline
    Timeline *mTimeline;

    /// Number of frames in the animation
    int mNumberOfFrames;

    /// Animation frame rate
    int mFrameRate;

	///machine start time
	int mMachineStartTime;

public:
    TimelineDlg(wxWindow* parent, Timeline *timeline);
};

#endif //CANADIANEXPERIENCE_TIMELINEDLG_H
