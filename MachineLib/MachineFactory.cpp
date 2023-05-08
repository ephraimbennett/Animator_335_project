/**
 * @file MachineFactory.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "MachineFactory.h"
#include "Machine.h"
#include "Shape.h"
#include "CardReader.h"
#include "AirSink.h"
#include "Pipe.h"
#include "Cylinder.h"
#include "StruckInstrument.h"
#include "Cymbal.h"
#include "Drum.h"
#include "Tubing.h"
#include "Clamp.h"

// constants
///the base width
const int BaseWidth = 700;

///the base height
const int BaseHeight = 10;


/**
 * Constructor
 * @param num
 * @param resourcesDir
 * @param engine
 */
MachineFactory::MachineFactory(int num, std::wstring resourcesDir, ma_engine* engine) : mResourcesDir(resourcesDir),
mAudioEngine(engine)
{
	mNum = num;
}

/**
 * Creates the machine
 * @return
 */
std::shared_ptr<Machine> MachineFactory::CreateMachine()
{
	//create machine
	auto machine = std::make_shared<Machine>(mNum);
	//assign position
//		machine->SetPosition(wxPoint(200, 500));

	// The base, just a flat to sit things on
	// centered at the origin
	auto base = std::make_shared<Shape>(mResourcesDir);
	base->Rectangle(-BaseWidth /2, BaseHeight / 2, BaseWidth, BaseHeight);
	base->SetColor(wxColour(100, 100, 100));
	machine->AddComponent(base);

	//the background
	//x drawn centered at the origin
	//y drawn so lower bound is at origin
	auto background = std::make_shared<Shape>(mResourcesDir);
	background->SetImage(L"/images/mortier.png");
	background->Rectangle(-background->GetImageWidth() / 2, 0);
	machine->AddComponent(background);

	//the card reader
	//drawn so that it sits right next to the background image.
	auto reader = std::make_shared<CardReader>(mResourcesDir);
	reader->SetCardPath(L"/images/cards/suzanna.png");
	reader->SetPosition(wxPoint(-(background->GetImageWidth() / 2) - reader->GetWidth() / 2, 0));
	machine->AddComponent(reader);
	reader->SetAirSources();

	//pipe it (also tube it)
	std::vector<std::shared_ptr<Pipe>> pipes;
	//location variables
	int PipeX = -100;
	const int PipeY = -100;
	const int PipeHeights[] = {200, 20, 100, 150,  70};
	const int PipeXOffset = 40;
	const int ClampPostCenter = -182;
	for (int i = 0; i < 5; i++)
	{
		auto pipe = std::make_shared<Pipe>(mResourcesDir, mAudioEngine, i,
										   PipeHeights[i]);
		pipe->SetPosition(wxPoint(PipeX + PipeXOffset * i, PipeY));
		machine->AddComponent(pipe);

		pipes.push_back(pipe);
	}

	//draw the stand for the drum cylinder
	auto block = std::make_shared<Shape>(mResourcesDir);
	block->SetImage( L"/images/angle-block.png");
	block->Rectangle(-block->GetImageWidth(), 0);   // 0,0 is lower right corner
	block->SetPosition(wxPoint(110, 0));
	machine->AddComponent(block);

	//draw the post for the clamps
	auto post = std::make_shared<Shape>(mResourcesDir);
	post->SetImage(L"/images/clamping-post.png");
	post->Rectangle(-post->GetImageWidth()/2, 0);
	post->SetPosition(wxPoint(ClampPostCenter, 0));
	machine->AddComponent(post);

	//create the clamps
	const wxPoint tlClampPos(-(background->GetImageWidth() / 2) + 50, -300);
	const int tlClampSpeed = 70;
	const double tlClampRotation = 0;
	auto topLeftClamp = std::make_shared<Clamp>(tlClampPos, tlClampRotation,tlClampSpeed);

	const int pClampSpeed = 100;
	const double pClampRotation = 0.0;
	const wxPoint pClampPos(ClampPostCenter, -50);
	auto postClampTop = std::make_shared<Clamp>(pClampPos, pClampRotation, pClampSpeed);

	//create the tube for the drum
	//literal 8 is used to indicate an "id" of 8, or the 9th row
	auto drumTube = std::make_shared<Tubing>(mResourcesDir, 8);
	reader->SetSink(drumTube->GetSink(), 8);
	drumTube->SetBegin(reader->GetAirSource(8)->GetLocation());
	drumTube->SetBeginningSpeed(200);
	drumTube->SetEndRotation(0.5);
	drumTube->AddClamp(postClampTop);

	//creat the tube for the cymbal
	auto cymbalTube = std::make_shared<Tubing>(mResourcesDir, 9);
	reader->SetSink(cymbalTube->GetSink(), 9);
	cymbalTube->SetBegin(reader->GetAirSource(9)->GetLocation());
	cymbalTube->AddClamp(topLeftClamp);


	//create the drum and its cylinder
	//some constants
	const double DrumCylinderRotation = 0.25;
	const int CylinderToInstrumentDistance = 100;
	const wxPoint DrumCylinderPos = wxPoint(100, -60);
	//first set up a cylinder
	auto cylinder1 = std::make_shared<Cylinder>(mResourcesDir);
	cylinder1->SetPosition(DrumCylinderPos);
	cylinder1->SetRotation(DrumCylinderRotation);
	//connect this cylinder to the drum tube
	drumTube->SetTarget(cylinder1->GetSink());
	drumTube->SetEnd(cylinder1->GetPosition());

	//set up a drum & give it the cylinder
	//some constants
	const int DrumX = DrumCylinderPos.x + CylinderToInstrumentDistance;
	auto kick = std::make_shared<Drum>(mResourcesDir, mAudioEngine, 8);
	kick->Rectangle(DrumX + kick->GetImageWidth() / 2, 0);
	cylinder1->SetInstrument(kick);

	//create a cymbal
	auto cymbal = std::make_shared<Cymbal>(mResourcesDir, mAudioEngine, 9);
	cymbal->SetPosition(wxPoint(DrumX, 0));
//	cymbal->Rectangle(DrumX, 0);

	//some constants
	const wxPoint CymbalCylinderPos(DrumX + cymbal->GetImageWidth() / 2, -cymbal->GetImageHeight() - CylinderToInstrumentDistance - 30);
	const double CymbalCylinderRotation = 0.5;
	auto cylinder2 = std::make_shared<Cylinder>(mResourcesDir);
	cylinder2->SetPosition(CymbalCylinderPos);
	cylinder2->SetRotation(CymbalCylinderRotation);
	cylinder2->SetInstrument(cymbal);
	//connect this cylinder to the cymbal tube
	cymbalTube->SetTarget(cylinder2->GetSink());
	cymbalTube->SetEnd(cylinder2->GetPosition());

	//draw order - instrument first, then cylinder. Drawing cymbal stuff before drum stuff
	machine->AddComponent(cymbal);
	machine->AddComponent(cylinder2);
	machine->AddComponent(kick);
	machine->AddComponent(cylinder1);



	//set up the tubes for the pipes
	for (int i = 0; i < 5; i++)
	{
		//grab the pipe
		auto pipe = pipes.at(i);

		//create the tube & set up proper connections
		auto tube = std::make_shared<Tubing>(mResourcesDir, i);
		reader->SetSink(tube->GetSink(), i);
		pipe->ConnectTube(tube);
		reader->SetSink(tube->GetSink(), i);

		//deal with graphics
		auto loc = reader->GetAirSource(i)->GetLocation();
		tube->SetBegin(loc);//set beginning location

		//add clamp post
		auto clamp = std::make_shared<Clamp>(wxPoint(ClampPostCenter, -10 + i * -15), 0.0, 100);
		tube->AddClamp(clamp);
		//set end point
		tube->SetEnd(pipe->GetPosition());

		//add to machine
		machine->AddComponent(tube);
	}

	//draw these tubes last
	machine->AddComponent(drumTube);
	machine->AddComponent(cymbalTube);

	// Clamping post clamps for the tubing
	auto clamps = std::make_shared<Shape>(mResourcesDir);
	clamps->SetImage(L"/images/clamping-post-clamps.png");
	clamps->Rectangle(-clamps->GetImageWidth()/2, 0);
	clamps->SetPosition(wxPoint(ClampPostCenter, 0));
	machine->AddComponent(clamps);

	return machine;

}
