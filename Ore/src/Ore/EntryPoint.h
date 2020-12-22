#pragma once
#include "Log.h"

#ifdef ORE_PLATFORM_WINDOWS 

extern Ore::App* Ore::CreateApplication();

int main(int argc, char** argv) {
	Ore::Log::Init();
	ORE_CORE_WARN("Initalized Log");
	ORE_INFO("Initalized App");

	auto app = Ore::CreateApplication();

	app->Run();

	delete app;
}

#endif