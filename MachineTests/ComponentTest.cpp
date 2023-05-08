/**
 * @file ComponentTest.cpp
 * @author Ephraim Bennett
 */

#include "pch.h"
#include "gtest/gtest.h"

#include <miniaudio.h>
#include <MachineSystemFactory.h>
#include <MachineSystem.h>
#include <MachineFactory.h>
#include <Component.h>
#include <Machine.h>

// Test fixture that creates an audio engine to use
class ComponentTest : public ::testing::Test {
protected:
	// The audio engine to use
	ma_engine mAudioEngine;

	void SetUp() override
	{
		auto result = ma_engine_init(NULL, &mAudioEngine);
		ASSERT_EQ(result, MA_SUCCESS);
	}

	void TearDown() override
	{
		ma_engine_uninit(&mAudioEngine);
	}

};

TEST_F(ComponentTest, AddToMachine)
{
	MachineFactory factory(0, L"");
	auto machine = factory.CreateMachine();

	auto component = std::make_shared<Component>();
	machine->AddComponent(component);

	auto c = machine->GetComponent(1);

	ASSERT_EQ(component, machine->GetComponent(1));
}