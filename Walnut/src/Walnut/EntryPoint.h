#pragma once

#ifdef WN_PLATFORM_WINDOWS

// Function defined in client, returns an application 
extern Walnut::Application* Walnut::CreateApplication(); 

int main(int argc, char** argv)
{
	// Starting log here for now
	Walnut::Log::Init();
	WN_CORE_INFO("Initialized Log!");

	auto app = Walnut::CreateApplication();
	app->Run();
	delete app;
}

#endif