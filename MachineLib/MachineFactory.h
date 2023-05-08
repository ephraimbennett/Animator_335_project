/**
 * @file MachineFactory.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY_H

#include "MachineSystemActual.h"
///forward references
class Machine;
struct ma_engine;

///Machine factory class
class MachineFactory
{
private:
	///the number this machine should make
	int mNum;

	///the resources directory
	std::wstring mResourcesDir;

	/// The miniaudio engine
	ma_engine* mAudioEngine;

	/// the machine's position
	wxPoint mPosition;

public:
	//disabling
	///default constructor (disabled)
	MachineFactory() = delete;

	///copy constructor (disabled)
	MachineFactory(const MachineFactory &) = delete;

	///assignment operatore (disabled)
	void operator=(const MachineFactory &) = delete;

	//constructor
	MachineFactory(int num, std::wstring resourcesDir, ma_engine* engine);

	std::shared_ptr<Machine> CreateMachine();

	/**
	 * Sets the position of the machine factory
	 * @param pos
	 */
	void SetPosition(wxPoint pos){mPosition = pos;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINEFACTORY_H
