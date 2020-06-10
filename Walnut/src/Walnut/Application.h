#pragma once
#include "Core.h"
#include "Log.h"
#include "Window.h"

namespace Walnut {

	class WALNUT_API Application
	{
	public:
		Application();
		virtual ~Application(); // This class is sub-classes by applications

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To de defined in CLIENT
	Application* CreateApplication();
}