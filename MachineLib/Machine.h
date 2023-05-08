/**
 * @file Machine.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

///forward references
class Component;

#include "MachineSystemActual.h"

///Machine class
class Machine
{
private:
	//member variables
	///the number of this machine
	int mMachineNumber = -1;

	///system time to be stored
	double mTime = 0.0;

	///the machine's position on the screen
	wxPoint mPosition;


	//associations
	///the system this machine belongs to
	MachineSystemActual* mMachineSystem = nullptr;

	///the list of components
	std::vector<std::shared_ptr<Component>> mComponents;

public:
	//constructors
	///default disabled
	Machine() = delete;

	///copy constructor disabled
	Machine(const Machine &) = delete;

	///assignment operator disabled
	void operator=(const Machine &) = delete;

	Machine(int num);


	//getters & setters
	/**
	 * Getter for position
	 * @return wxPoint object
	 */
	wxPoint GetPosition() { return mPosition;}

	/**
	 * Setter for position
	 * @param pos
	 */
	void SetPosition(wxPoint pos) {mPosition = pos;}

	void SetMachineSystem(MachineSystemActual* system);

	/**
	 * Gets a specific component from this machine
	 * @param idx
	 * @return
	 */
	std::shared_ptr<Component> GetComponent(int idx){return mComponents.at(idx);}

	//other functions
	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	void UpdateTime(double time);

	void AddComponent(std::shared_ptr<Component>);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
