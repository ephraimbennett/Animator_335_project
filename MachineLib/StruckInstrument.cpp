/**
 * @file StruckInstrument.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "StruckInstrument.h"
#include "Cylinder.h"

/**
 * Constructor
 * @param resourcesDir
 * @param engine
 * @param id
 */
StruckInstrument::StruckInstrument(std::wstring resourcesDir, ma_engine * engine, int id) : Instrument(resourcesDir,
engine, id){

}

/**
 * function to call when struck
 * @param flag
 */
void StruckInstrument::Strike(bool flag)
{
	PlaySound();
}
