/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"

using namespace std;

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @param audioEngine The audio engine to use in this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir, ma_engine* audioEngine)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    shared_ptr<Picture> picture = make_shared<Picture>();

    // Create the background and add it
    auto background = make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

	//create and add the machine
	std::wstring name = L"machine_system";
	auto machineActor = std::make_shared<Actor>(name);
	auto machineDrawable = std::make_shared<MachineDrawable>(name,resourcesDir, audioEngine);
	machineActor->SetRoot(machineDrawable);
	machineDrawable->SetPosition(wxPoint(500, 500));
	machineDrawable->SetTimeline(picture->GetTimeline());
	machineActor->AddDrawable(machineDrawable);
	picture->AddActor(machineActor);
	picture->SetMachineDrawable(machineDrawable);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(600, 610));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(900, 620));
    picture->AddActor(sparty);

	return picture;
}

