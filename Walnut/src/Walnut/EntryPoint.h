#pragma once

#ifdef WN_PLATFORM_WINDOWS

// Function defined in client, returns an application 
extern Walnut::Application* Walnut::CreateApplication(); 

int main(int argc, char** argv)
{
	// Starting log here for now
	Walnut::Log::Init();
	WN_CORE_WARN("Initialized Log!");
	int a = 5;
	WN_INFO("Hello! Var={0}", a);

	auto app = Walnut::CreateApplication();
	app->Run();
	delete app;
}

#endif