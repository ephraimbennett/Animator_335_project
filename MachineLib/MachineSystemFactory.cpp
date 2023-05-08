/**
 * @file MachineSystemFactory.cpp
 *
 * @author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "MachineSystemFactory.h"
#include "MachineSystem.h"
#include "MachineSystemActual.h"
#include "MachineFactory.h"
#include "MachineTwoFactory.h"

/**
 * Constructor
 * @param resourcesDir Directory to load resources from
 * @param audioEngine The miniaudio engine to use
 */
MachineSystemFactory::MachineSystemFactory(std::wstring resourcesDir, ma_engine* audioEngine) :
    mResourcesDir(resourcesDir), mAudioEngine(audioEngine)
{
}


/**
 * Create a machine system object
 *
 * Do not change the return type of this function!
 *
 * @return Object of type MachineSystem
 */
std::shared_ptr<MachineSystem> MachineSystemFactory::CreateMachineSystem()
{
	auto system =  std::make_shared<MachineSystemActual>();

	//now, create the machines
	MachineFactory factory1(0, mResourcesDir, mAudioEngine);
	auto machine = factory1.CreateMachine();

	MachineTwoFactory factory2(1, mResourcesDir, mAudioEngine);
	auto machine2 = factory2.CreateMachine();

	//add the machine & return
	system->AddMachine(machine);
	system->AddMachine(machine2);

	return system;
}


