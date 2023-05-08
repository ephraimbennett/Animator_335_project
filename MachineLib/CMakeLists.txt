project(MachineLib)

set(SOURCE_FILES
        pch.h
        MachineSystem.h MachineSystem.cpp
        MachineSystemFactory.cpp MachineSystemFactory.h
        MachineStandin.cpp MachineStandin.h
        Polygon.cpp Polygon.h
        MachineDialog.cpp MachineDialog.h include/machine-api.h
        MachineSystemActual.h MachineSystemActual.cpp Machine.h Machine.cpp
        MachineFactory.h MachineFactory.cpp Component.cpp Component.h Shape.cpp Shape.h CardReader.cpp CardReader.h AirSource.cpp AirSource.h AirSink.cpp AirSink.h Instrument.cpp Instrument.h Pipe.cpp Pipe.h Cylinder.cpp Cylinder.h StruckInstrument.cpp StruckInstrument.h Cymbal.cpp Cymbal.h Drum.cpp Drum.h Tubing.cpp Tubing.h Clamp.cpp Clamp.h MachineTwoFactory.cpp MachineTwoFactory.h)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Fetch miniaudio from Github
include(FetchContent)
FetchContent_Declare(
        miniaudio
        GIT_REPOSITORY https://github.com/mackron/miniaudio.git
        GIT_TAG 1778a5e839514f35f41d31449f3573e3adffc51a # Version 0.11.10
)

FetchContent_MakeAvailable(miniaudio)

target_include_directories(${PROJECT_NAME} PUBLIC "${miniaudio_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)