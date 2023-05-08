/**
 * @file Component.h
 * @author Ephraim Bennett
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

///forward references
class Machine;

///Component class
class Component
{
private:
	///the path to its image
	std::wstring mImageFile;

	///time state
	double mTime = 0;

	//associations
	///pointer to the machine
	Machine * mMachine = nullptr;
protected:
	///component's position
	wxPoint mPosition;

	///rotary orientation
	double mOrientation = 0;

	///string to the resources directory
	std::wstring mResourcesDir;

public:
	//constructor
	///default deleted
	Component() = delete;

	///copy constructor delete
	Component(const Component &) = delete;

	///assignment operator delete
	void operator=(const Component &) = delete;

	Component(std::wstring resourcesPath);

	//methods
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	virtual void Update(double time);

	void SetMachine(Machine *);

	/**
	 * Gets a pointer to the machine
	 * @return mMachine
	 */
	Machine * GetMachine() {return mMachine;}

	/**
	 * Sets the orientation for this component
	 * @param rotation
	 */
	virtual void SetRotation(double rotation) {mOrientation = rotation;}

	/**
	 * Getter for orientation
	 * @return double
	 */
	virtual double GetRotation() {return mOrientation;}

	/**
	 * Sets the position of this component
	 * @param pos
	 */
	virtual void SetPosition(wxPoint pos) {mPosition = pos;}

	/**
	 * Gets the position
	 * @return
	 */
	virtual wxPoint GetPosition() {return mPosition;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
