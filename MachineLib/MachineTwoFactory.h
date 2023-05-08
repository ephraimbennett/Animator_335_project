/**
 * @file MachineTwoFactory.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINETWOFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINETWOFACTORY_H

///forward references
class Machine;
struct ma_engine;

///The machine factory for machine number two
class MachineTwoFactory
{
private:
	///the machine number
	int mNum;

	///the resources directory
	std::wstring mResourcesDir;

	/// The miniaudio engine
	ma_engine* mAudioEngine;

	/// the machine's position
	wxPoint mPosition;
public:

	MachineTwoFactory(int num, std::wstring resourcesDir, ma_engine* engine);

	///default constructor (disabled)
	MachineTwoFactory() = delete;

	///copy constructor (disabled)
	MachineTwoFactory(const MachineTwoFactory &) = delete;

	///assignment operatore (disabled)
	void operator=(const MachineTwoFactory &) = delete;

	std::shared_ptr<Machine> CreateMachine();

	/**
	 * Sets the location of the machine we are creating
	 * @param loc
	 */
	void SetLocation(wxPoint loc) {mPosition = loc;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINETWOFACTORY_H
