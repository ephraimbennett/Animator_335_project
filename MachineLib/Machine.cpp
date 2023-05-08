/**
 * @file Machine.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"

/**
 * Constructor
 * @param num
 */
Machine::Machine(int num) : mMachineNumber(num)
{

}

/**
 * Sets the system for this machine
 * @param system
 */
void Machine::SetMachineSystem(MachineSystemActual * system)
{
	mMachineSystem = system;
}

/**
 * Draw function - called from MachineSystemActual
 * @param graphics
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	for (auto comp : mComponents)
	{
		comp->Draw(graphics);
	}

}

/**
 * Updates time
 * @param time
 */
void Machine::UpdateTime(double time)
{
	mTime = time;
	for (auto comp : mComponents)
	{
		comp->Update(time);
	}
}

/**
 * Adds a component
 * @param component
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
	mComponents.push_back(component);
	component->SetMachine(this);
}

