#pragma once

#ifdef WN_PLATFORM_WINDOWS

// Function defined in client, returns an application 
extern Walnut::Application* Walnut::CreateApplication(); 

int main(int argc, char** argv)
{
	printf("Starting Walnut!");
	auto app = Walnut::CreateApplication();
	app->Run();
	delete app;
}

#endif