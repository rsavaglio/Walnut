#pragma once
#include "Core.h"
#include "Log.h"

namespace Walnut {

	class WALNUT_API Application
	{
	public:
		Application();
		virtual ~Application(); // This class is sub-classes by applications

		void Run();
	};

	// To de defined in CLIENT
	Application* CreateApplication();
}