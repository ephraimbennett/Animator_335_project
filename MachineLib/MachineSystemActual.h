/**
 * @file MachineSystemActual.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H

#include "MachineSystem.h"

///forward references
class Machine;
class MainFrame;

///The actual machine system
class MachineSystemActual : public MachineSystem
{
private:
	//member variables
	///int that represents which machine we are on
	int mCurrentMachine = 0;

	///int to indicate which frame we are one
	int mFrameNum = 0;

	///double to indicate the framerate
	double mFrameRate = 0.0;

	///double to store the time our system is on
	double mTime = 0.0;

	//associations
	///vector of machine objects
	std::vector<std::shared_ptr<Machine>> mMachines;
public:
	//constructor
	MachineSystemActual();

	//getters and setters
	/**
	 * Getter for the machine num - overridden
	 * @return int for machine num
	 */
	int GetMachineNumber() override {return mCurrentMachine;}

	/**
	 * Setter for machine num - overridden
	 */
	void SetMachineNumber(int num) override;

	/**
	 * Getter for machine time - overridden
	 * @return double for the time
	 */
	double GetMachineTime() override {return mTime;}

	/**
	 * Setter for the frame rate
	 * @param rate
	 */
	void SetFrameRate(double rate) override {mFrameRate = rate;}

	/**
	 * Gets the machine used in the machine system
	 * @return
	 */
	std::shared_ptr<Machine> GetMachine(){return mMachines.at(mCurrentMachine);}

	//other methods
	void SetMachineFrame(int frame) override;

	void SetLocation(wxPoint location) override;

	void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);

	void UpdateMachine();

	void AddMachine(std::shared_ptr<Machine> machine);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
