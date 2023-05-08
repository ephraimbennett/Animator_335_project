/**
 * @file MachineTwoFactory.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "MachineTwoFactory.h"
#include "Machine.h"
#include "Shape.h"
#include "CardReader.h"
#include "Pipe.h"
#include "Cylinder.h"
#include "Drum.h"
#include "Cymbal.h"
/**
 * Constructor
 * @param num
 * @param resourcesDir
 * @param engine
 */
MachineTwoFactory::MachineTwoFactory(int num, std::wstring resourcesDir, ma_engine *engine) : mResourcesDir(resourcesDir),
mAudioEngine(engine)
{

}

/**
 * Creates the machine
 * @return shared pointer to the machine
 */
std::shared_ptr<Machine> MachineTwoFactory::CreateMachine()
{
	auto machine = std::make_shared<Machine>(2);

	//the background
	//x drawn centered at the origin
	//y drawn so lower bound is at origin
	auto background = std::make_shared<Shape>(mResourcesDir);
	background->SetImage(L"/images/mortier.png");
	background->Rectangle(-background->GetImageWidth() / 2, 0);
	machine->AddComponent(background);

	//the card reader
	//placed to the left of the background
	auto reader = std::make_shared<CardReader>(mResourcesDir);
	reader->SetCardPath(L"/images/cards/mary.png");
	reader->SetPosition(wxPoint(-(background->GetImageWidth() / 2) - reader->GetWidth() / 2, 0));
	machine->AddComponent(reader);
	reader->SetAirSources();

	//create the pipes
	std::vector<std::shared_ptr<Pipe>> pipes;
	const int PipeHeights[] = {100, 100, 50, 50, 300};
	const int PipeYLoc = -50;
	const int PipeXStart = -100;
	const int PipeSpacing = 12;
	for (int i = 0; i < 5; i++)
	{
		auto pipe = std::make_shared<Pipe>(mResourcesDir, mAudioEngine, i,
										   PipeHeights[i]);
		pipe->SetPosition(wxPoint(PipeXStart + i * PipeSpacing, PipeYLoc));
		pipes.push_back(pipe);
		machine->AddComponent(pipe);
	}

	//make the cylinders
	const wxPoint CylinderDrumLoc(background->GetImageWidth() / 2 + 100, -50);
	const double CylinderDrumRotation = -0.25;
	auto cylinderDrum = std::make_shared<Cylinder>(mResourcesDir);
	cylinderDrum->SetPosition(CylinderDrumLoc);
	cylinderDrum->SetRotation(CylinderDrumRotation);


	const wxPoint CylinderCymbalLoc(background->GetImageWidth() / 2 + 115, -240);
	const double CylinderCymbalRotation = 0.72;
	auto cylinderCymbal = std::make_shared<Cylinder>(mResourcesDir);
	cylinderCymbal->SetPosition(CylinderCymbalLoc);
	cylinderCymbal->SetRotation(CylinderCymbalRotation);


	//make the drum
	const wxPoint DrumLocation(background->GetImageWidth() / 2 - 100, 0);
	const double DrumRotation = 0.5;
	auto drum = std::make_shared<Drum>(mResourcesDir, mAudioEngine, 8);
	drum->SetPosition(DrumLocation);
	drum->Rectangle(-drum->GetImageWidth(), drum->GetImageHeight());
	drum->SetRotation(DrumRotation);
	cylinderDrum->SetInstrument(drum);


	//make the cymbal
	const wxPoint CymbalLocation(background->GetImageWidth() / 2 - 100, 0);
	auto cymbal = std::make_shared<Cymbal>(mResourcesDir, mAudioEngine, 9);
	cymbal->SetPosition(CymbalLocation);
	cylinderCymbal->SetInstrument(cymbal);

	//draw the drum on top of the cymbal
	machine->AddComponent(cymbal);
	machine->AddComponent(drum);
	//draw the cylinders on top of their instruments, so we can see when they strike them
	machine->AddComponent(cylinderDrum);
	machine->AddComponent(cylinderCymbal);

	//create tubing for the pipes
	auto pipeClamp = std::make_shared<Clamp>(wxPoint(0, 20), 0.0, 100);
	for (int i = 0; i < 5; i++)
	{
		auto pipe = pipes.at(i);//grab the pipe

		//create the tube & set up proper connections
		auto tube = std::make_shared<Tubing>(mResourcesDir, i);
		reader->SetSink(tube->GetSink(), i);
		pipe->ConnectTube(tube);

		//deal with graphics
		auto loc = reader->GetAirSource(i)->GetLocation();
		tube->SetBegin(loc);//set beginning location
//		tube->AddClamp(pipeClamp);
		tube->SetEnd(pipe->GetPosition());

		machine->AddComponent(tube);
	}

	//create the tube for the drum
	auto drumTube = std::make_shared<Tubing>(mResourcesDir, 8);
	reader->SetSink(drumTube->GetSink(), 8);
	drumTube->SetTarget(cylinderDrum->GetSink());
	auto loc = reader->GetAirSource(8)->GetLocation();
	drumTube->SetBegin(loc);
	drumTube->SetEnd(cylinderDrum->GetPosition());
	machine->AddComponent(drumTube);

	//create the tube for the cymbal
	auto cymbalTube = std::make_shared<Tubing>(mResourcesDir, 9);
	reader->SetSink(cymbalTube->GetSink(), 9);
	cymbalTube->SetTarget(cylinderCymbal->GetSink());
	loc = reader->GetAirSource(9)->GetLocation();
	cymbalTube->SetBegin(loc);
	cymbalTube->SetEnd(cylinderCymbal->GetPosition());
	machine->AddComponent(cymbalTube);

	return machine;
}
