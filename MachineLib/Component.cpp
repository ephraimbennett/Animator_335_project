/**
 * @file Component.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include <sstream>
#include "Component.h"
#include "Machine.h"

/**
 * Constructor that only initializes with the path to the resources directory
 * @param resourcesPath
 */
Component::Component(std::wstring resourcesPath) : mResourcesDir(resourcesPath)
{

}

/**
 * Draws this component
 * @param graphics
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{


}

/**
 * Update as time changes
 * @param time
 */
void Component::Update(double time)
{
	mTime = time;
}

/**
 * Sets the machine that this component belongs to
 * @param machine
 */
void Component::SetMachine(Machine * machine)
{
	mMachine = machine;
}



