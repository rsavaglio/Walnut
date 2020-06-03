#include "Application.h"

namespace Walnut {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);

		// Test, should only be logged once
		if (e.IsInCategory(EventCategoryInput))
		{
			WN_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryApplication))
		{
			WN_TRACE(e);
		}

 		while (true); // Simple
	}
}