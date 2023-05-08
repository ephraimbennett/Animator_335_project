/**
 * @file MachineSystemActual.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "MachineSystemActual.h"
#include "Machine.h"
#include "MachineDialog.h"

/**
 * Constructor default
 */
MachineSystemActual::MachineSystemActual()
{
	SetMachineNumber(2);
}

/**
 * Updates the machine based on what frame we are on
 */
void MachineSystemActual::UpdateMachine()
{

	mTime = mFrameNum / mFrameRate;
	mMachines.at(mCurrentMachine - 1)->UpdateTime(mTime);
}

/**
 * Sets the location of the machine
 * @param location
 */
void MachineSystemActual::SetLocation(wxPoint location)
{
	mMachines.at(mCurrentMachine - 1)->SetPosition(location);
}

/**
 * Override call to draw function
 * @param graphics
 */
void MachineSystemActual::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
	mMachines.at(mCurrentMachine - 1)->Draw(graphics);
}

/**
 * Adds a new machine to this system
 * @param machine
 */
void MachineSystemActual::AddMachine(std::shared_ptr<Machine> machine)
{
	mMachines.push_back(machine);
	machine->SetMachineSystem(this);
}

/**
 * Sets the current frame the machine is on.
 * Updates time to correspond correctly.
 * @param frame
 */
void MachineSystemActual::SetMachineFrame(int frame)
{
	mFrameNum = frame;
	UpdateMachine();
}

/**
 * Sets the machine number and controls for out of bounds inputs
 * @param num
 */
void MachineSystemActual::SetMachineNumber(int num)
{
	mCurrentMachine = num;
}
