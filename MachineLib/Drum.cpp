/**
 * @file Drum.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "Drum.h"

///image path for the drum
const std::wstring DrumImagePath = L"/images/drum.png";

/**
 * Constructor
 * @param resourcesDir
 * @param engine
 * @param id
 */
Drum::Drum(std::wstring resourcesDir, ma_engine *engine, int id) : StruckInstrument(resourcesDir, engine, id)
{
	SetImage(DrumImagePath);
}

/**
 * Override implementation of draw
 * @param graphics
 */
void Drum::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	Shape::Draw(graphics);
}

/**
 * Override implementation of update
 * @param time
 */
void Drum::Update(double time)
{
	Shape::Update(time);
}

/**
 * over
 * @param rotation
 */
void Drum::SetRotation(double rotation)
{
	Shape::SetRotation(rotation);
}

